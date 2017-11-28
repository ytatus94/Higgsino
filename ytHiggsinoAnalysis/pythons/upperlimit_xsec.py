#!/usr/bin/python
'''
This script makes the upper limit plot of the cross-section
'''
import ROOT, AtlasStyle
import os, array

#------------------------------

def main():
    xsecs = read_cross_section('/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/ytHiggsinoAnalysis/misc/NUHM2_Weak.txt')
    sum_xsecs = sum_cross_section(xsecs)
    # uls = read_upper_limit('../misc/NUHM2_all_points_upperlimit_upperlimit_only_reweighting_NoSys_doNewFFs.csv')
    # uls = read_upper_limit('../misc/NUHM2_all_points_upperlimit_upperlimit_only_reweighting_AllSys_doNewFFs.csv')
    uls = read_upper_limit('../misc/NUHM2_all_points_upperlimit_upperlimit_only_Judita_MCprod_AllSys_doNewFFs.csv')
    # uls = read_upper_limit('../misc/test.csv')
    masses = read_masses('/Users/ytshen/Documents/Working/OU/HEP/Abe/WeakSLHA/')
    plot_upper_limit(sum_xsecs, uls, masses, True)

#------------------------------

def read_cross_section(file):
    '''
    Read the DSID, FS, cross-section, k-Factor, filter efficiency, and uncertainty
    from the SUSYTools cross-section file
    '''
    xsecs = []
    with open(file) as fopen:
        for line in fopen.readlines():
            if line[0] is not '#':
                items = line.split()
                if len(items) > 0:
                    #SAMPLE   FS     CROSSECTION[pb]  K-FACTOR/BF   FILTEREFF    REL.UNCERT
                    dsid = int(items[0])
                    fs   = int(items[1])
                    xsec = float(items[2])
                    kfac = float(items[3])
                    eff  = float(items[4])
                    unc  = float(items[5])
                    xsecs.append({'dsid':dsid, 'fs':fs, 'xsec':xsec, 'kfac':kfac, 'eff':eff, 'unc':unc})
    return xsecs

#------------------------------

def sum_cross_section(xsecs):
    '''
    Sum the cross-sections of N2N1, C1C1, N2C1p, and N2C1m
    So one m12 mass point has only one set of (xsec, xsec_up, xsec_down)
    '''
    list_xsecs = []
    for i in range(0, len(xsecs)):
        # Only select the new Weak DSID
        if xsecs[i]['dsid'] >= 394301 and xsecs[i]['dsid'] <= 394328: # new Weak DSID
            xsec = xsecs[i]['xsec']
            unc = xsecs[i]['unc']
            xsec_up = xsec * (1 + unc)
            xsec_down = xsec * (1 - unc)
            m12 = 0
            if xsecs[i]['dsid'] >= 394301 and xsecs[i]['dsid'] <= 394304: # m12 = 300
                m12 = 300
            elif xsecs[i]['dsid'] >= 394305 and xsecs[i]['dsid'] <= 394308: # m12 = 350
                m12 = 350
            elif xsecs[i]['dsid'] >= 394309 and xsecs[i]['dsid'] <= 394312: # m12 = 400
                m12 = 400
            elif xsecs[i]['dsid'] >= 394313 and xsecs[i]['dsid'] <= 394316: # m12 = 500
                m12 = 500
            elif xsecs[i]['dsid'] >= 394317 and xsecs[i]['dsid'] <= 394320: # m12 = 600
                m12 = 600
            elif xsecs[i]['dsid'] >= 394321 and xsecs[i]['dsid'] <= 394324: # m12 = 700
                m12 = 700
            elif xsecs[i]['dsid'] >= 394325 and xsecs[i]['dsid'] <= 394328: # m12 = 800
                m12 = 800
            list_xsecs.append({'m12':m12, 'xsec':xsec, 'xsec_up':xsec_up, 'xsec_down':xsec_down})

    list_m12 = []
    for i in range(0, len(list_xsecs)):
        if list_xsecs[i]['m12'] not in list_m12:
            list_m12.append(list_xsecs[i]['m12'])

    sum_xsecs = []
    for m12 in list_m12:
        sum_xsec, sum_xsec_up, sum_xsec_down = 0, 0, 0
        for i in range(0, len(list_xsecs)):
            if list_xsecs[i]['m12'] == m12:
                sum_xsec += list_xsecs[i]['xsec']
                sum_xsec_up += list_xsecs[i]['xsec_up']
                sum_xsec_down += list_xsecs[i]['xsec_down']
        sum_xsecs.append({'m12':m12, 'sum_xsec':sum_xsec, 'sum_xsec_up':sum_xsec_up, 'sum_xsec_down':sum_xsec_down})

    return sum_xsecs
#------------------------------

def read_upper_limit(file):
    '''
    Read the upper limit form csv file.
    All the values represent mu_SIG
    '''
    uls = []
    with open(file) as fopen:
        for line in fopen.readlines():
            if 'mSUSY' not in line:
                items = line.split(',')
                # mSUSY,mLSP,dM_SUSY_LSP,upperLimit,expectedUpperLimit,expectedUpperLimitMinus1Sig,expectedUpperLimitPlus1Sig,,expectedUpperLimitMinus2Sig,expectedUpperLimitPlus2Sig
                m12 = int( float(items[0]) )
                ul_obs = float(items[3])
                ul_exp = float(items[4])
                ul_expm1s = float(items[5])
                ul_expp1s = float(items[6])
                ul_expm2s = float(items[7])
                ul_expp2s = float(items[8])
                uls.append({'m12':m12, 'ul_obs':ul_obs, 'ul_exp':ul_exp, 'ul_expm1s':ul_expm1s, 'ul_expp1s':ul_expp1s, 'ul_expm2s':ul_expm2s, 'ul_expp2s':ul_expp2s})

    return uls

#------------------------------

def read_masses(input_dir):
    '''
    Read the masses of N2, N1, and C1 from the SLHA files.
    Calculate the dm = M(N2) - M(N1)
    '''
    masses = []
    for slha in os.listdir(input_dir):
        if slha.endswith("slha"):
            m12 = int( slha[slha.find('m12_') + len('m12_'):slha.find('m12_') + len('m12_')+3] )
            mass_n2, mass_n1, mass_c1, dm = 0, 0, 0, 0
            with open(input_dir + '/' + slha) as fopen:
                read_buffer = False
                for line in fopen.readlines():
                    if "Block MASS" in line:
                        read_buffer = True
                    if "Block ALPHA" in line:
                        read_buffer = False
                    if read_buffer and '#  PDG code' not in line:
                        if "#  z1ss" in line:
                            mass_n1 = abs( float(line.split()[1]) )
                        elif "#  z2ss" in line:
                            mass_n2 = abs( float(line.split()[1]) )
                        elif "#  w1ss" in line:
                            mass_c1 = abs( float(line.split()[1]) )
                        if mass_n2 != 0 and mass_n1 != 0 and mass_n2 > mass_n1:
                            dm = mass_n2 - mass_n1
                masses.append({'m12':m12, 'mass_n2':mass_n2, 'mass_n1':mass_n1, 'mass_c1':mass_c1, 'dm':dm})

    return masses

#------------------------------

def plot_upper_limit(sum_xsecs, uls, masses, UL_label):
    xmin = 350
    xmax = 800
    ymin = 0.9
    ymax = 500

    pad_title = "NUHM2:  m_{0}=5 TeV, A_{0}=-1.6m_{0}, tan#beta=15, #mu=150 GeV, m_{A}=1 TeV"
    x_title = "m_{1/2} [GeV]"
    y_title = "#sigma_{NUHM2} (#font[12]{pp #rightarrow #tilde{#chi}^{0}_{2}#tilde{#chi}^{#pm}_{1}, #tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{1}, #tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#pm}_{1}}) [pb]"
    titles = pad_title + ";" + x_title + ";" + y_title

    # TGraph
    gul_obs = ROOT.TGraph()
    gul_exp = ROOT.TGraph()

    gul_exp1s = ROOT.TGraphAsymmErrors()
    gul_exp2s = ROOT.TGraphAsymmErrors()

    g_xsec = ROOT.TGraph()
    g_xsec_up = ROOT.TGraph()
    g_xsec_down = ROOT.TGraph()

    # Fill the TGraph
    n = len(uls) # n = 6, from 350
    m = len(sum_xsecs) # m = 7, from 300

    for i in range(0, n):
        # j = i + 1 # i starts from 350 but j starts from 300
        # print 'm12=', uls[i]['m12'], 'mu_SIG=', uls[i]['ul_obs'], 'xsec=', sum_xsecs[j]['sum_xsec'], 'xsec*mu_SIG=', uls[i]['ul_obs'] * sum_xsecs[j]['sum_xsec']
        for j in range(0, m):
            if uls[i]['m12'] == sum_xsecs[j]['m12']:
                gul_obs.SetPoint(i, uls[i]['m12'], uls[i]['ul_obs'] * sum_xsecs[j]['sum_xsec'])
                gul_exp.SetPoint(i, uls[i]['m12'], uls[i]['ul_exp'] * sum_xsecs[j]['sum_xsec'])

                eyl_1s = abs( (uls[i]['ul_expm1s'] - uls[i]['ul_exp']) * sum_xsecs[j]['sum_xsec'] )
                eyh_1s = abs( (uls[i]['ul_expp1s'] - uls[i]['ul_exp']) * sum_xsecs[j]['sum_xsec'] )
                gul_exp1s.SetPoint(i, uls[i]['m12'], uls[i]['ul_exp'] * sum_xsecs[j]['sum_xsec'])
                gul_exp1s.SetPointError(i, 0., 0., eyl_1s, eyh_1s)

                eyl_2s = abs( (uls[i]['ul_expm2s'] - uls[i]['ul_exp']) * sum_xsecs[j]['sum_xsec'] )
                eyh_2s = abs( (uls[i]['ul_expp2s'] - uls[i]['ul_exp']) * sum_xsecs[j]['sum_xsec'] )
                gul_exp2s.SetPoint(i, uls[i]['m12'], uls[i]['ul_exp'] * sum_xsecs[j]['sum_xsec'])
                gul_exp2s.SetPointError(i, 0., 0., eyl_2s, eyh_2s)

    for j in range(0, m):
        g_xsec.SetPoint(j, sum_xsecs[j]['m12'], sum_xsecs[j]['sum_xsec'])
        g_xsec_up.SetPoint(j, sum_xsecs[j]['m12'], sum_xsecs[j]['sum_xsec_up'])
        g_xsec_down.SetPoint(j, sum_xsecs[j]['m12'], sum_xsecs[j]['sum_xsec_down'])

    # Set the TGraph
    color_obs = ROOT.TColor.GetColor("#aa000")
    color_exp = ROOT.TColor.GetColor("#28373c")
    color_yellow = ROOT.TColor.GetColor("#ffe938")

    gul_obs.SetLineStyle(1)
    gul_exp.SetLineStyle(7)
    gul_exp1s.SetLineStyle(1)
    gul_exp2s.SetLineStyle(1)
    g_xsec.SetLineStyle(1)
    g_xsec_up.SetLineStyle(2)
    g_xsec_down.SetLineStyle(2)

    gul_obs.SetLineColor(color_obs)
    gul_exp.SetLineColor(color_exp)
    gul_exp1s.SetLineColor(ROOT.kGreen)
    gul_exp2s.SetLineColor(color_yellow)
    g_xsec.SetLineColor(ROOT.kBlue)
    g_xsec_up.SetLineColor(ROOT.kBlue)
    g_xsec_down.SetLineColor(ROOT.kBlue)

    gul_obs.SetLineWidth(4)
    gul_exp.SetLineWidth(3)
    gul_exp1s.SetLineWidth(2)
    gul_exp2s.SetLineWidth(2)
    g_xsec.SetLineWidth(2)
    g_xsec_up.SetLineWidth(2)
    g_xsec_down.SetLineWidth(2)

    gul_exp1s.SetFillStyle(1001)
    gul_exp2s.SetFillStyle(1001)

    gul_exp1s.SetFillColor(ROOT.kGreen)
    gul_exp2s.SetFillColor(color_yellow)

    leg = ROOT.TLegend(0.52, 0.65, 0.87, 0.87)
    leg.AddEntry(g_xsec, "pp #rightarrow #tilde{#chi}^{0}_{2}#tilde{#chi}^{#pm}_{1}, #tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{1}, #tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#pm}_{1}", "l")
    leg.AddEntry(g_xsec_up, "Theoretical uncertainty", "l")
    leg.AddEntry(gul_exp, "Expected limit", "l")
    leg.AddEntry(gul_obs, "Observed limit", "l")
    leg.AddEntry(gul_exp1s, "Expected #pm 1#sigma_{exp}", "f")
    leg.AddEntry(gul_exp2s, "Expected #pm 2#sigma_{exp}", "f")
    leg.SetBorderSize(0);
    leg.SetTextFont(42);
    leg.SetTextSize(0.03);
    leg.SetFillColor(0);
    leg.SetFillStyle(0);

    # TGraph
    # g_dm = ROOT.TGraph() # x: m12, y: dm
    # for i in range(0, len(masses)):
    #     g_dm.SetPoint(i, masses[i]['m12'], masses[i]['dm'])
    # print g_dm.Eval(350), g_dm.Eval(400), g_dm.Eval(500), g_dm.Eval(600), g_dm.Eval(700), g_dm.Eval(800)

    g_m12 = ROOT.TGraph() # x: dm, y: m12
    for i in range(0, len(masses)):
        g_m12.SetPoint(i, masses[i]['dm'], masses[i]['m12'])
    # print g_m12.Eval(20), g_m12.Eval(25), g_m12.Eval(30), g_m12.Eval(35), g_m12.Eval(40), g_m12.Eval(45)

    c = ROOT.TCanvas("c", "Upper limit", 600, 800)
    ROOT.gStyle.SetOptStat(0)

    right_margin = 0.05
    left_margin = 0.13

    # Upper plot will be in pad1
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.15, 1, 0.98)
    pad1.SetTopMargin(0.08)
    pad1.SetBottomMargin(0.15)
    pad1.SetRightMargin(right_margin)
    pad1.SetLeftMargin(left_margin)
    # pad1.SetFillColor(42)
    # pad1->SetGridy() # grid lines
    pad1.Draw()

    # lower plot will be in pad
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.02, 1, 0.15)
    pad2.SetTopMargin(0.05)
    pad2.SetBottomMargin(0.3)
    pad2.SetRightMargin(right_margin)
    pad2.SetLeftMargin(left_margin)
    # pad2.SetFillColor(16)
    # pad2.SetGridy() # grid lines
    pad2.Draw()

    pad1.cd()
    pad1.SetLogy()
    pad1.SetTickx()
    pad1.SetTicky()

    frame1 = pad1.DrawFrame(xmin, ymin, xmax, ymax, titles)
    frame1.GetXaxis().SetTitleOffset(1.15)
    frame1.GetXaxis().SetTitleSize(0.045)
    frame1.GetXaxis().SetLabelOffset(0.015)
    frame1.GetXaxis().SetLabelSize(0.03)
    frame1.GetYaxis().SetTitleOffset(1.3)
    frame1.GetYaxis().SetTitleSize(0.045)
    frame1.GetYaxis().SetLabelOffset(0.015)
    frame1.GetYaxis().SetLabelSize(0.03)

    gul_exp2s.Draw("L3")
    gul_exp1s.Draw("L3")
    gul_obs.Draw("L")
    gul_exp.Draw("L")
    g_xsec.Draw("L")
    g_xsec_up.Draw("L")
    g_xsec_down.Draw("L")
    leg.Draw()

    AtlasStyle.ATLASLabel(0.18, 0.80, "Internal", ROOT.kBlack)
    AtlasStyle.myText(0.18, 0.73, "#sqrt{s} = 13 TeV, 36.1 fb^{-1}", ROOT.kBlack, 0.04)

    AtlasStyle.myText(0.61, 0.62, "All limits at 95% CL", ROOT.kBlack, 0.03)
    AtlasStyle.myText(0.61, 0.585, "ee/#mu#mu, m_{#font[12]{l}#font[12]{l}} shape fit", ROOT.kBlack, 0.03)
    AtlasStyle.myText(0.61, 0.54, "#tilde{#chi}^{0}_{2} #rightarrow Z* #tilde{#chi}^{0}_{1}, #tilde{#chi}^{#pm}_{1} #rightarrow W* #tilde{#chi}^{0}_{1}", ROOT.kBlack, 0.03)

    if UL_label:
        label = ROOT.TLatex()
        label.SetTextFont(42)
        label.SetTextSize(0.024)
        label.SetTextColor(ROOT.kGray+2)
        label.SetTextAngle(45)
        # label.SetNDC()
        for i in range(0, n): # n = len(uls)
            for j in range(0, m):
                if uls[i]['m12'] == sum_xsecs[j]['m12']:
                    x_value = uls[i]['m12']
                    y_value = uls[i]['ul_obs'] * sum_xsecs[j]['sum_xsec']
                    label_text = '{:04.2f}'.format(y_value)
                    if x_value == 350:
                        x_value += 10
                    if x_value == 800:
                        x_value -= 15
                    label.DrawLatex(x_value, y_value+0.5, label_text)

    # 1 and 2 sigma bands cover the y ticks.
    # we need to redraw the axis to show the ticks
    pad1.Update()
    pad1.RedrawAxis()

    # Draw the dm axis on pad2
    pad2.cd()
    
    # Draw an axis without ticks and labels.
    # This is used for a axis line and title only
    gaxis = ROOT.TGaxis(left_margin, 0.7, 1 - right_margin, 0.7, 0, 1, 0, "")
    gaxis.SetTitle("m_{#tilde{#chi}^{0}_{2}} - m_{#tilde{#chi}^{0}_{1}} [GeV]")
    gaxis.SetTitleFont(42)
    gaxis.SetTitleSize(0.28)
    gaxis.SetLabelFont(42)
    gaxis.SetLabelSize(0)
    gaxis.SetTickLength(0)
    gaxis.SetLineWidth(2)
    gaxis.Draw()

    # Make ticks and labels by myself
    l_tick_left = ROOT.TLine(left_margin, 0.7, left_margin, 0.85)
    l_tick_left.SetLineWidth(2)
    l_tick_left.Draw()
    l_tick_right = ROOT.TLine(1 - right_margin, 0.7, 1 - right_margin, 0.85)
    l_tick_right.SetLineWidth(2)
    l_tick_right.Draw()

    # Ticks
    # g_m12.Eval(350) = 46.057022 
    # g_m12.Eval(400) = 38.168159
    # g_m12.Eval(500) = 28.016555
    # g_m12.Eval(600) = 22.049652
    # g_m12.Eval(700) = 18.192032
    # g_m12.Eval(800) = 15.495697
    # So the small ticks from 16 to 45
    list_ticks = []
    list_labels = []
    for tick in [16, 17, 18, 19,
                 20, 21, 22, 23, 24,
                 25, 26, 27, 28, 29,
                 30, 31, 32, 33, 34,
                 35, 36, 37, 38, 39,
                 40, 41, 42, 43, 44,
                 45]:
        tick_x_value = left_margin + (g_m12.Eval(tick) - 350.) / (800. - 350.) * (1 - right_margin - left_margin)
        if tick in [20, 25, 30, 35, 40, 45]:
            l_tick = ROOT.TLine(tick_x_value, 0.7, tick_x_value, 0.85)
            tick_label = ROOT.TLatex(tick_x_value - 0.01, 0.48, str(tick))
            tick_label.SetTextFont(42)
            tick_label.SetTextSize(0.2)
            list_labels.append(tick_label)
        else:
            l_tick = ROOT.TLine(tick_x_value, 0.7, tick_x_value, 0.78)
        list_ticks.append(l_tick)
    for tick in list_ticks:
        tick.Draw()
    for tick_label in list_labels:
        tick_label.Draw()

    c.SaveAs("nuhm2_UL.pdf")

#------------------------------

if __name__ == '__main__':
    main()
