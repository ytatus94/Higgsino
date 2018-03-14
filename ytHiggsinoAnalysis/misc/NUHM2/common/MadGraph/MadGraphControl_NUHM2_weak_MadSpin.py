from MadGraphControl.MadGraphUtils import *

if not hasattr(runArgs,'runNumber'):
  raise RunTimeError("No run number found.")

#--------------------------------------------------------------
# Extract input: slha, filters, decay generator, process
#--------------------------------------------------------------
# Jo and run name
# e.g. MC15.123456.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_N2C1p_2LMET50_MadSpin.py
joname = runArgs.jobConfig[0]
run_name = joname.split("_")[2]+"_"+joname.split("_")[3]+"_"+joname.split("_")[4]+"_"+joname.split("_")[5]+"_"+joname.split("_")[6]
# SLHA
slha_name = "susy."+str(runArgs.runNumber)+"."+run_name+".slha"
# Filters
filters = ""
do2LFilter = False
if "2L" in joname: 
    do2LFilter = True
    filters += "2L"
doMETFilter = False
if "MET" in joname: 
    doMETFilter = True
    filters += "MET"
    metcut = int((joname.split("_")[7]).split("MET")[1])
# Decay generator
decay_gen = "Pythia"
if "MadGraph" in joname: decay_gen = "MadGraph"
elif "MadSpin" in joname: decay_gen = "MadSpin"
else: print "... No decay generator specified, using default", decay_gen
# Process
proc = ""
if "N2C1p" in joname: proc = "N2C1p"
elif "N2C1m" in joname: proc = "N2C1m"
elif "N2N1" in joname: proc = "N2N1"
elif "C1C1" in joname: proc = "C1C1"
else: proc = "All"
# Arrange the MG output
runArgs.inputGeneratorFile="madgraph.{0}.Madgraph_{1}._00001.events.tar.gz".format(runArgs.runNumber,(joname.split(".")[2]).strip("MGPy8EG_")) 

print "#####################################################"
print "Using input:"
print "run name   = ", run_name
print "jobOptions = ", joname
print "LesHouches = ", slha_name
print "Filters    = ", filters
print "METCut     = ", metcut
print "Generator  = ", decay_gen
print "Process    = ", proc
print "Genfile    = ", runArgs.inputGeneratorFile
print "#####################################################"

# Define prcess and decay strings:
# MadGraph decays, MadGraph process, MadSpin decays, Pythia merge process
procs = {}

procs["N2C1p"] = {"mgdecay": ", (n2 > l+ l- n1), (x1+ > all all n1)",
                  "mgproc": "p p > n2 x1+",
                  "msdecay": "decay n2 > l+ l- n1\ndecay x1+ > f f n1\n",
                  "mergeproc": "{n2,1000023}{x1+,1000024}"}
procs["N2C1m"] = {"mgdecay": ", (n2 > l+ l- n1), (x1- > all all n1)",
                  "mgproc": "p p > n2 x1-",
                  "msdecay": "decay n2 > l+ l- n1\ndecay x1- > f f n1\n",
                  "mergeproc": "{n2,1000023}{x1-,-1000024}"}
procs["C1C1"]  = {"mgdecay": ", (x1+ > l+ vl n1), (x1- > l- vl~ n1)",
                  "mgproc": "p p > x1+ x1-",
                  "msdecay": "decay x1+ > l+ vl  n1\ndecay x1- > l- vl~ n1\n",
                  "mergeproc": "{x1+,1000024}{x1-,-1000024}"}
procs["N2N1"]  = {"mgdecay": ", (n2 > l+ l- n1)",
                  "mgproc": "p p > n2 n1",
                  "msdecay": "decay n2 > l+ l- n1\n",
                  "mergeproc": "{n2,1000023}{n1,1000022}"}
if proc not in procs.keys(): print "Process not implemented", proc

#--------------------------------------------------------------
# MadGraph5 processes card
#--------------------------------------------------------------
# Define process for MadGraph
process='''
import model mssm
define p = g u c d s b u~ c~ d~ s~ b~
define j = g u c d s b u~ c~ d~ s~ b~
define l+ = e+ mu+ ta+
define l- = e- mu- ta-
define vl = ve vm vt
define vl~ = ve~ vm~ vt~
define lv = e+ mu+ ta+ e- mu- ta- ve vm vt ve~ vm~ vt~
define f = e+ mu+ ta+ e- mu- ta- ve vm vt ve~ vm~ vt~ u u~ d d~ c c~ s s~ b b~ g
define sleptons = el- el+ er- er+ mul- mul+ mur- mur+ ta1- ta1+ ta2- ta2+ h+ h- svt svm sve svt~ svm~ sve~
'''

# Write out the processes for njets
# If using MadGraph process and MadGraph decays, set MadGraph process and MadGraph decays
# If using MadGraph process and MadSpin decays, set just MadGraph process, set MadSpin decays later (with launch command)
# If using MadGraph process and Pythia decays, set just MadGraph process, and leave default for processes (i.e. don't launch MadSpin later) 
njets = 2
for i in xrange(njets+1):
  process += "%-12s %s %-10s %s @%d\n" % ('generate' if i==0 else 'add process',
                                          procs[proc]["mgproc"],
                                          ' j'*i,
                                          "" if decay_gen != "MadGraph" else procs[proc]["mgdecay"],
                                          i+1)
process += "output -f"

# Write out the proc card
proc_card_name = 'proc_card_mg5.dat'
fcard = open(proc_card_name,'w')
fcard.write(process)
fcard.close()
if False:
    print "==> MadGraph proc card:"
    print process

#--------------------------------------------------------------
# MadSpin decays card
#--------------------------------------------------------------
# Define decays when using MadSpin decay generator, write the madspin card, and launch
if decay_gen == "MadSpin":
    msdecaystring = procs[proc]["msdecay"]
    msdecays = """#************************************************************
#*                        MadSpin                           *
#*                                                          *
#*    P. Artoisenet, R. Frederix, R. Rietkerk, O. Mattelaer *
#*                                                          *
#*    Part of the MadGraph5_aMC@NLO Framework:              *
#*    The MadGraph5_aMC@NLO Development Team - Find us at   *
#*    https://server06.fynu.ucl.ac.be/projects/madgraph     *
#*                                                          *
#************************************************************
#Some options (uncomment to apply)
#
# set Nevents_for_max_weigth 75 # number of events for the estimate of the max. weight
set BW_cut 100                # cut on how far the particle can be off-shell
set max_weight_ps_point 400  # number of PS to estimate the maximum for each event
#
set seed %i
set spinmode none 
# specify the decay for the final state particles

%s

# running the actual code
launch"""%(runArgs.randomSeed,msdecaystring)

    madspin_card_name = "madspin_card_higgsino.dat"
    mscard = open(madspin_card_name,'w')
    mscard.write(msdecays)
    mscard.close()

    if False:
        print "==> MadSpin decays card:"
        print msdecays

#--------------------------------------------------------------
# Pythia merge procs
#--------------------------------------------------------------
# Merge processes with Pythia
mergeproc = procs[proc]["mergeproc"]
mergeproc+="LEPTONS,NEUTRINOS"
if False:
    print "==> Pythia mergeproc:"
    print mergeproc

#--------------------------------------------------------------
# Event filters and multipliers
#--------------------------------------------------------------
evt_multiplier = 1.
filters = []
# Adding 2L filter with 3 GeV cut, and increasing event multiplier
if do2LFilter:
    evt_multiplier*=100.0
    include('MC15JobOptions/MultiLeptonFilter.py')
    from GeneratorFilters.GeneratorFiltersConf import MultiElecMuTauFilter
    filtSeq += MultiElecMuTauFilter("MultiElecMuTauFilter")
    ElecMuTauFilter = filtSeq.MultiElecMuTauFilter
    ElecMuTauFilter.MinPt = 3000.
    ElecMuTauFilter.MaxEta = 2.8
    ElecMuTauFilter.NLeptons = 2
    ElecMuTauFilter.IncludeHadTaus = 0    # don't include hadronic taus

    if decay_gen == "Pythia":
       # if there's a Z in the event, and we have pythia decaying things, the only way to get 2 leptons is to have Z->ll
       genSeq.Pythia8.Commands += ["23:onMode = off", #switch off all Z decays
                                   "23:onIfAny = 11 13 15"] # switch on Z->ll
    filters.append("MultiElecMuTauFilter")
# Adding the MET filter of 50 GeV, and increasing event multiplier
if doMETFilter:
    evt_multiplier*=20.0
    include ( 'MC15JobOptions/MissingEtFilter.py' )
    from GeneratorFilters.GeneratorFiltersConf import MissingEtFilter
    if not hasattr(filtSeq, "MissingEtFilter"):
      filtSeq += MissingEtFilter("MissingEtFilter")
     
    if not hasattr(filtSeq, "MissingEtFilterUpperCut"):
      filtSeq += MissingEtFilter("MissingEtFilterUpperCut")
   
    filtSeq.MissingEtFilter.METCut = metcut*GeV
    filtSeq.MissingEtFilterUpperCut.METCut = 100000*GeV
    filters.append("MissingEtFilter and not MissingEtFilterUpperCut")

# Need to add the list of fitlers, workaround for a bug in MadGraph
for i in filters:
    if filtSeq.Expression == "":
        filtSeq.Expression=i
    else:
        filtSeq.Expression = "(%s) and (%s)" % (filtSeq.Expression,i)

#--------------------------------------------------------------
# Defualts
#--------------------------------------------------------------
# Numer of events to be generated
nevts = runArgs.maxEvents if runArgs.maxEvents > 0 else 5000
# Beam energy
beamEnergy=6500
if hasattr(runArgs,'ecmEnergy'): beamEnergy = runArgs.ecmEnergy / 2.
else: raise RunTimeError("No center of mass energy found.")
# Extras for MadGraph, change defaults for run_card.dat
runArgs.qcut = 15. # low matching scale, following DM group recommendations
if njets==0: runArgs.qcut = 0
extras = {  'lhe_version': '2.0', 
            #'ktdurham':runArgs.qcut ,
            'cut_decays':'F' ,
            'pdlabel':"'nn23lo1'",
            'lhaid':'247000',
            'parton_shower':'PYTHIA8',
            'drjj': 0.0,
            'ptj': 10,       
            'ptl': 0,
            'etal': '-1.0',
            'drll': 0.0,
            'drjl': 0.0,
            'auto_ptj_mjj': 'F',
            'bwcutoff': 100 # to allow very low-mass W* and Z*
          }

#--------------------------------------------------------------
# Build MadGraph and run cards
#--------------------------------------------------------------
print "#####################################################"
print "run_card_old=","run_card.dat" # get_default_runcard()
print "xqcut=       ",runArgs.qcut
print "nevts=       ",nevts*evt_multiplier
print "rand_seed=   ",runArgs.randomSeed
print "beamEnergy=  ",beamEnergy
print "extras=      ",extras
print "#####################################################"

# Generate parameter card from lesHouches file
param_card_name = slha_name
from PyJobTransformsCore.trfutil import get_files
get_files(param_card_name, keepDir=True, errorIfNotFound=True)

# Generate the new process with MadGraph
process_dir = new_process(card_loc=proc_card_name)
run_card_name = build_run_card(run_card_old=get_default_runcard(proc_dir=process_dir),
                               xqcut=runArgs.qcut,
                               nevts=nevts*evt_multiplier,
                               rand_seed=runArgs.randomSeed,
                               beamEnergy=beamEnergy,
                               extras=extras)

print_cards()

print "#####################################################"
print "run_card_loc= %s"%run_card_name
print "param_card_loc=" ,param_card_name
print "run_name=",run_name
print "proc_dir=",process_dir
print "#####################################################"

#--------------------------------------------------------------
# Generate events with MadGraph
#--------------------------------------------------------------
# If MadSpin specified, add it to the generate command, otherwise it is 
# specified with MadGraph decays, or set to default when Pythia is used
if decay_gen == "MadSpin":
    generate(run_card_loc= "%s"%run_card_name,
             madspin_card_loc=madspin_card_name,
             param_card_loc=param_card_name,
             mode=0,
             njobs=1,
             run_name=run_name,
             proc_dir=process_dir)
else:
    generate(run_card_loc= "%s"%run_card_name,
             param_card_loc=param_card_name,
             mode=0,
             njobs=1,
             run_name=run_name,
             proc_dir=process_dir)

#skip_events = 0
if hasattr(runArgs,'skipEvents'): skip_events = runArgs.skipEvents
arrange_output(run_name=run_name,
               proc_dir=process_dir,
               outputDS=runArgs.inputGeneratorFile)

#--------------------------------------------------------------
# Pythia8 showering with A14_NNPDF23LO
#--------------------------------------------------------------
include("MC15JobOptions/Pythia8_A14_NNPDF23LO_EvtGen_Common.py")
include("MC15JobOptions/Pythia8_MadGraph.py")

genSeq.Pythia8.Commands += ["Init:showAllParticleData = on",
                            "Next:numberShowLHA = 10",
                            "Next:numberShowEvent = 10",
                            ]
if njets>0:
    genSeq.Pythia8.Commands += ["Merging:mayRemoveDecayProducts = on",
                                "Merging:nJetMax = "+str(njets),
                                "Merging:doKTMerging = on",
                                "Merging:TMS = "+str(runArgs.qcut),
                                "Merging:ktType = 1",
                                "Merging:Dparameter = 0.4",
                                "Merging:nQuarksMerge = 4",
                                "Merging:Process = pp>%s" % mergeproc,
                                "1000037:spinType = 1",
                                "1000035:spinType = 1",
                                "1000025:spinType = 1",
                                "1000024:spinType = 1",
                                "1000023:spinType = 1",
                                "1000022:spinType = 1"]

#print genSeq.Pythia8.Commands

#--------------------------------------------------------------
# MC15 metadata
#--------------------------------------------------------------
evgenConfig.contact = ["judita.mamuzic@cern.ch"]
evgenConfig.description = "NUHM2 model with weak production split per processes and using MadSpin for the decays."
#evgenConfig.inputfilecheck = runArgs.inputGeneratorFile.split('._0')[0]
evgenConfig.keywords = ["SUSY"]
evgenConfig.process = "weak/weak"


