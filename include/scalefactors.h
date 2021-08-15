#ifndef scalefactors_h
#define scalefactors_h

class PNetHbbScaleFactors
{
    public: 
        TFile *file_sf;       
        TH2D *PNetXBBSF;
        
        PNetHbbScaleFactors(string year)
        {
            file_sf = new  TFile("data/scale_factor/PNetXBB_SF_v2.root");
            PNetXBBSF =   (TH2D*)file_sf->Get(("PNetXBBSF_"+year).data());  
            PNetXBBSF->SetDirectory(0);           
            file_sf->Close();               
        }
        ~PNetHbbScaleFactors()
        {
            delete PNetXBBSF;
        }
        //get the trigger eff per AK8 jet
        float getPNetHbbScaleFactors(float pt, float PNetXbb, int ibinx, int ibiny, int variation) 
        {
            if( pt > PNetXBBSF->GetXaxis()->GetXmax() * 0.999 ) {
                    pt = PNetXBBSF->GetXaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_x = PNetXBBSF->GetXaxis()->FindFixBin(pt);
            int bin_index_y = PNetXBBSF->GetYaxis()->FindFixBin(PNetXbb);
            
            int nbin_x = PNetXBBSF->GetNbinsX();
            int nbin_y = PNetXBBSF->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
                if( (variation==1) && (ibinx == bin_index_x) && (ibiny == bin_index_y) ){
                    result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y) + PNetXBBSF->GetBinError(bin_index_x, bin_index_y);
                }
                else if( (variation==-1) && (ibinx == bin_index_x) && (ibiny == bin_index_y) ){
                    result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y) - PNetXBBSF->GetBinError(bin_index_x, bin_index_y);
                }
                else result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y);
            }   
 
            return result;
        }
};

class TrigEffScaleFactors
{
    public: 
        TFile *file_sf;
        
        TH2F *hist_sf_Xbb0p0To0p9;
        TH2F *hist_sf_Xbb0p9To0p95;
        TH2F *hist_sf_Xbb0p95To0p98;
        TH2F *hist_sf_Xbb0p98To1p0;
        
        int Nbin_Xbb0p0To0p9 = 0;
        int Nbin_Xbb0p9To0p95 = 0;
        int Nbin_Xbb0p95To0p98 = 0;
        int Nbin_Xbb0p98To1p0 = 0;
        
        int nbin_x_Xbb0p0To0p9 = 0;
        int nbin_y_Xbb0p0To0p9 = 0;
        
        int nbin_x_Xbb0p9To0p95 = 0;
        int nbin_y_Xbb0p9To0p95 = 0;
        
        int nbin_x_Xbb0p95To0p98 = 0;
        int nbin_y_Xbb0p95To0p98 = 0;
        
        int nbin_x_Xbb0p98To1p0 = 0;
        int nbin_y_Xbb0p98To1p0 = 0;

        
        TrigEffScaleFactors(string year)
        {
            if(year == "2016") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2016.root");
            else if(year == "2017") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2017.root");
            else if(year == "2018") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2018.root");

            hist_sf_Xbb0p0To0p9 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p0To0p9");
            hist_sf_Xbb0p9To0p95 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p9To0p95");
            hist_sf_Xbb0p95To0p98 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p95To0p98");
            hist_sf_Xbb0p98To1p0 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p98To1p0");   
            
            hist_sf_Xbb0p0To0p9->SetDirectory(0);
            hist_sf_Xbb0p9To0p95->SetDirectory(0);
            hist_sf_Xbb0p95To0p98->SetDirectory(0);
            hist_sf_Xbb0p98To1p0->SetDirectory(0);
            
            file_sf->Close();
            
            Nbin_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetYaxis()->GetNbins()*hist_sf_Xbb0p0To0p9->GetXaxis()->GetNbins();
            Nbin_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetYaxis()->GetNbins()*hist_sf_Xbb0p9To0p95->GetXaxis()->GetNbins();
            Nbin_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetYaxis()->GetNbins()*hist_sf_Xbb0p95To0p98->GetXaxis()->GetNbins();
            Nbin_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetYaxis()->GetNbins()*hist_sf_Xbb0p98To1p0->GetXaxis()->GetNbins();  
            
            nbin_x_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetXaxis()->GetNbins();
            nbin_y_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetXaxis()->GetNbins();
            nbin_y_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetXaxis()->GetNbins();
            nbin_y_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetXaxis()->GetNbins();
            nbin_y_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetYaxis()->GetNbins();
                
        }
        ~TrigEffScaleFactors()
        {
            delete hist_sf_Xbb0p0To0p9;
            delete hist_sf_Xbb0p9To0p95;
            delete hist_sf_Xbb0p95To0p98;
            delete hist_sf_Xbb0p98To1p0;
        }
        //get the trigger eff per AK8 jet
        float getTriggerEff3D(float pt, float mass, float PNetXbb, int variation, int ibin) 
        {
            //cout <<"ibin in getTriggerEff3D: "<<ibin<<endl;
            float result = 0.0;
            float tmpMass = 0;
            float tmpPt = 0;
            TH2F* trigEffHist = 0;
            
            int ibin_start = 0; //0
            int nbin_x = 0;
            
            if (PNetXbb < 0.9){
                trigEffHist = hist_sf_Xbb0p0To0p9;
                nbin_x = nbin_x_Xbb0p0To0p9;
            }
            else if (PNetXbb < 0.95){ 
                trigEffHist = hist_sf_Xbb0p9To0p95; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9;
                nbin_x = nbin_x_Xbb0p9To0p95;
            }
            else if (PNetXbb < 0.98){ 
                trigEffHist = hist_sf_Xbb0p95To0p98; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95; 
                nbin_x = nbin_x_Xbb0p95To0p98;
            }  
            else{ 
                trigEffHist = hist_sf_Xbb0p98To1p0; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95 + Nbin_Xbb0p95To0p98; 
                nbin_x = nbin_x_Xbb0p98To1p0;
            }    
            
            if (trigEffHist) {
                // constrain to histogram bounds for mass and pT of Jet
                if( mass > trigEffHist->GetXaxis()->GetXmax() * 0.999 ) {
                    tmpMass = trigEffHist->GetXaxis()->GetXmax() * 0.999;
                } 
                else if ( mass < trigEffHist->GetXaxis()->GetXmin() * 1.001 ) {
                    tmpMass = trigEffHist->GetXaxis()->GetXmin();
                } 
                else {
                    tmpMass = mass;
                }
    
                if( pt > trigEffHist->GetYaxis()->GetXmax() * 0.999 ) {
                    tmpPt = trigEffHist->GetYaxis()->GetXmax() * 0.999;
                } 
                else if (pt < trigEffHist->GetYaxis()->GetXmin() * 1.001) {
                    tmpPt = trigEffHist->GetYaxis()->GetXmin() * 1.001;
                    //cout << "Warning: pt=" << pt << " is smaller than the trigger SF meaured range\n";
                } 
                else {
                   tmpPt = pt;
                }
                int bin_index_x = trigEffHist->GetXaxis()->FindFixBin(tmpMass);
                int bin_index_y = trigEffHist->GetYaxis()->FindFixBin(tmpPt);
                //cout <<"variation PNetXbb tmpMasss tmpPt "<<variation<<" "<< PNetXbb<<" "<<tmpMass<<" "<<tmpPt<<endl;
                //cout <<"bin_index_x, bin_index_y"<<bin_index_x<<" "<<bin_index_y<<endl;
                //cout <<"ibin ibin_start + (bin_index_y-1)*nbin_x + bin_index_x "<<ibin<<" "<< ibin_start + (bin_index_y-1)*nbin_x + bin_index_x <<endl;

                if( variation==0 ){
                   result = trigEffHist->GetBinContent(bin_index_x, bin_index_y); 
                   //cout <<"eff for object "<<result<<endl;
                }
                else if( ibin == (ibin_start + (bin_index_y-1)*nbin_x + bin_index_x) ){
                    if( variation==1 ){
                        result = trigEffHist->GetBinContent(bin_index_x, bin_index_y) + trigEffHist->GetBinError(bin_index_x, bin_index_y);
                        //cout <<"trig unc up "<<endl;
                    }
                    else if( variation==-1 ){
                        result = trigEffHist->GetBinContent(bin_index_x, bin_index_y) - trigEffHist->GetBinError(bin_index_x, bin_index_y);
                        //cout <<"trig unc down"<<endl;
                    }
                }
                else result = trigEffHist->GetBinContent(bin_index_x, bin_index_y);  
            } 
            else {
                //std::cout << "Error: expected a histogram, got a null pointer" << std::endl;
                return 0;
            }
            //cout <<"eff per jet: "<<result<<endl;
            return result;
        }
        //get the trigger eff per event
        float getTrigEffEvt(float pt1, float mass1, float PNetXbb1, float pt2, float mass2, float PNetXbb2, int variation, int ibin){
            //cout <<"ibin in getTrigEffEvt: "<<ibin<<endl;
            float eff = 1.0 - (1.0 - getTriggerEff3D(pt1, mass1, PNetXbb1, variation, ibin))*(1.0 - getTriggerEff3D(pt2, mass2, PNetXbb2, variation, ibin));
            return eff;
        }
        //get the number of systematic uncertainties sources (number of bins in trigger map)
        int getNbins(){
            int Nbins = Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95 + Nbin_Xbb0p95To0p98 + Nbin_Xbb0p98To1p0;
            return Nbins;
        }
        //get the SF ratio of variation/nominal 
        float get_unc_ratio(float pt1, float mass1, float PNetXbb1, float pt2, float mass2, float PNetXbb2, int variation, int itrig_unc){           
            float tmp = 0;
            //cout <<"ibin in get_unc_ratio: "<<itrig_unc<<endl;           
            float nominal = getTrigEffEvt(pt1, mass1, PNetXbb1, pt2, mass2, PNetXbb2, 0, 0);     
            if( nominal!=0 ){
                tmp = getTrigEffEvt(pt1, mass1, PNetXbb1, pt2, mass2, PNetXbb2, variation, itrig_unc)/nominal;   
                //if (tmp!=1) cout <<" ratio for itrig_unc: "<< itrig_unc<<" "<<tmp<< endl;
            } 
            return tmp;
        }
};

class TTJetsScaleFactors
{
    public: 
        TFile *file_sf_2016;
        TFile *file_sf_2017;
        TFile *file_sf_2018;
        TH1F *hist_sf_2016;
        TH1F *hist_sf_2017;
        TH1F *hist_sf_2018;
        TTJetsScaleFactors()
        {
            file_sf_2016 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2016.root");
            file_sf_2017 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2017.root");
            file_sf_2018 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2018.root");

            hist_sf_2016 =   (TH1F*)file_sf_2016->Get("ratio_data_over_mc");
            hist_sf_2017 =   (TH1F*)file_sf_2017->Get("ratio_data_over_mc");
            hist_sf_2018 =   (TH1F*)file_sf_2018->Get("ratio_data_over_mc");
            
            hist_sf_2016->SetDirectory(0);
            hist_sf_2017->SetDirectory(0);
            hist_sf_2018->SetDirectory(0);
            
            file_sf_2016->Close();
            file_sf_2017->Close();
            file_sf_2018->Close();
        }
        ~TTJetsScaleFactors()
        {
            //file_sf_2016->Close();
            //file_sf_2017->Close();
            //file_sf_2018->Close();

            delete hist_sf_2016;
            delete hist_sf_2017;
            delete hist_sf_2018;
        }
        float getScaleFactors(string year, float pt)
        {
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            if(year ==  "2016")
            {
                result  = hist_sf_2016->GetBinContent(hist_sf_2016->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2017")
            {
                result  = hist_sf_2017->GetBinContent(hist_sf_2017->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2018")
            {
                result  = hist_sf_2018->GetBinContent(hist_sf_2018->GetXaxis()->FindFixBin(pt));
            }
            if(result <0.01) result = 1.0;
            if(result >3.0) result = 1.0;
            return result;
        }
        //Ramp model 
        float getScaleFactorsFitv0(string year, float pt, int type=0)
        {
            //type: 0, 1, -1 for norminal Up, Down
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            //default values are for 2018
            float slope = 0.00148792, constant = 1.12203; //par1, par0
            float cov00 = 0.00203, cov01 = 9.163e-06, cov11 = 4.938e-08;
            if(year == "2016")
            {
                slope = 0.000291232, constant = 1.10197; //par1, par0
                cov00 = 0.004345, cov01 = 1.969e-05, cov11 = 1.079e-07;
            }
            if(year == "2017")
            {
                slope = 0.00177981, constant = 1.31793; //par1, par0
                cov00 = 0.003392, cov01 = 1.519e-05, cov11 = 8.042e-08;
            }
            if(year == "2018")
            {
                slope = 0.00148792, constant = 1.12203; //par1, par0
                cov00 = 0.00203, cov01 = 9.163e-06, cov11 = 4.938e-08;
            }
            if(pt<300) result = slope*(pt-300.) + constant + type*sqrt((pt-300.)*(pt-300.)*cov11 + cov00 + 2*(pt-300)*cov01);
            else result = constant + type*sqrt(cov00);
            //if(result <0.01) result = 1.0;
            //if(result >3.0) result = 1.0;
            return result;
        }
        //two linear functions
        float getScaleFactorsFit(string year, float pt, int type=0)
        {
            //type: 0, 1, -1 for norminal Up, Down
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            //default values are for 2018
            float slope2 = -8.90051e-04, slope1 = 8.93903e-04, constant1 = 9.66787e-01; //par2, par1, par0  of the fit function
            float cov00 = 0.002517, cov01 = -1.618e-05, cov02 = 5.18e-06; //elements of the covariance matrix
            float cov11 = 1.521e-07, cov12 = -6.53e-08, cov22 = 9.643e-08; //elements of the covariance matrix
            if(year == "2016")
            {
                slope2 = -8.90051e-04, slope1 = 8.93903e-04, constant1 = 9.66787e-01; //par2, par1, par0
                cov00 = 0.002517, cov01 = -1.618e-05, cov02 = 5.18e-06;
                cov11 = 1.521e-07, cov12 = -6.53e-08, cov22 = 9.643e-08;
            }
            if(year == "2017")
            {
                slope2 = -4.27981e-04, slope1 = 1.99119e-03, constant1 = 7.67781e-01; //par2, par1, par0
                cov00 = 0.001671, cov01 = -1.096e-05, cov02 = 4.099e-06;
                cov11 = 1.068e-07, cov12 = -5.345e-08, cov22 = 1.082e-07;
            }
            if(year == "2018")
            {
                slope2 = -5.52196e-04, slope1 = 1.79594e-03, constant1 = 6.51474e-01; //par2, par1, par0
                cov00 = 0.001079, cov01 = -6.96e-06, cov02 = 2.348e-06;
                cov11 = 6.606e-08, cov12 = -2.991e-08, cov22 = 5.363e-08;
            }
            if(pt<300) result = slope1*pt + constant1 + type*sqrt(pt*pt*cov11 + cov00 + 2*pt*cov01);
            else if(pt<1000.) result = constant1 + 300.*slope1 + (pt-300.)*slope2 + type*sqrt(cov00 + 300.*300.*cov11 + (pt-300.)*(pt-300.)*cov22 + 2*300.*cov01 + 2*(pt - 300.)*cov02 + 2*300.*(pt-300.)*cov12);
            else result = constant1 + 300.*slope1 + (1000.-300.)*slope2 + 1.5*type*sqrt(cov00 + 300.*300.*cov11 + (1000.-300.)*(1000.-300.)*cov22 + 2*300.*cov01 + 2*(1000. - 300.)*cov02 + 2*300.*(1000.-300.)*cov12);
            return result;
        }
        float getPNetXbbShapeScaleFactors(string year, float xbb, int type=0)
        {
            //type: 0, 1, -1 for nominal Up Down
            int idx_xbb  = 0;
            if(xbb < 0.945) idx_xbb  = 0;
            else if (xbb  < 0.955) idx_xbb =1;
            else if (xbb  < 0.975) idx_xbb =2;
            else if (xbb < 0.985) idx_xbb =3;
            else idx_xbb = 4;
            if (year == "2016")
            {
               float sf[5] = {0.821, 0.789, 0.824, 0.701, 0.741};
               float esf[5] = {0.012, 0.066, 0.044, 0.084, 0.069};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2017")
            {
               float sf[5] = {0.901, 0.880, 0.876, 0.860, 0.916};
               float esf[5] = {0.014, 0.067, 0.045, 0.064, 0.071};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2018")
            {
               float sf[5] = {0.975, 1.024, 0.935, 0.890, 0.798};
               float esf[5] = {0.016, 0.059, 0.039, 0.055, 0.056};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            return 1.0;
        }

};

double TopTagSF( string workingPoint, string year, double pt ) {
  double result = 1.0;
  if (workingPoint == "0.40") {
    if (year == "2016") {
      if (pt > 600) {
	result = 0.930;
      } else if (pt > 480) {
	result = 1.013;
      } else if (pt > 400) {
	result = 1.041;
      } else if (pt > 300) {
	result = 0.926;
      } else {
	result = 0.926; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else if (year == "2017") {
      if (pt > 600) {
	result = 0.760;
      } else if (pt > 480) {
	result = 0.851;
      } else if (pt > 400) {
	result = 0.856;
      } else if (pt > 300) {
	result = 0.879;
      } else {
	result = 0.879; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else if (year == "2018") {
      if (pt > 600) {
	result = 0.787;
      } else if (pt > 480) {
	result = 0.911;
      } else if (pt > 400) {
	result = 0.923;
      } else if (pt > 300) {
	result = 0.888;
      } else {
	result = 0.888; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }
  else if (workingPoint == "0.46") {
    if (year == "2016") {
      if (pt > 600) {
    result = 1.00;
      } else if (pt > 480) {
    result = 0.988;
      } else if (pt > 400) {
    result = 0.976;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
    else if (year == "2017") {
      if (pt > 600) {
    result = 0.87;
      } else if (pt > 480) {
    result = 0.89;
      } else if (pt > 400) {
    result = 0.95;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
    else if (year == "2018") {
      if (pt > 600) {
    result = 0.847;
      } else if (pt > 480) {
    result = 0.93;
      } else if (pt > 400) {
    result = 0.976;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
   else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }  else {
    cout << "[TopTagSF] Warning: workingPoint=" << workingPoint << " is not supported\n";
  }
  return result;
};

class miniIsoEleScaleFactors
{
    public: 
        TFile *file_sf;       
        TH2F *miniIsoSF;

        miniIsoEleScaleFactors(string year)
        {
	  TString fname = "data/scale_factor/ElectronScaleFactors_Run"+year+".root";
	  file_sf = new  TFile(fname);
	  TString hname = "Run"+year+"_Mini2";
	  miniIsoSF =   (TH2F*)file_sf->Get(hname);
          
       
        }
        ~miniIsoEleScaleFactors()
        {
	  delete miniIsoSF;
	  file_sf->Close();                                                                                                                                                                               
	  
        }
        //get the trigger eff per AK8 jet
        float getminiIsoScaleFactors(float pt, float eta) 
        {
	  if( pt > miniIsoSF->GetYaxis()->GetXmax() * 0.999 ) {
                    pt = miniIsoSF->GetYaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_x = miniIsoSF->GetXaxis()->FindFixBin(eta);
            int bin_index_y = miniIsoSF->GetYaxis()->FindFixBin(pt);
            
            int nbin_x = miniIsoSF->GetNbinsX();
            int nbin_y = miniIsoSF->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
	      result = miniIsoSF->GetBinContent(bin_index_x, bin_index_y);
	    }  
 
            return result;
        }
};
class miniIsoMuScaleFactors
{
    public: 
        TFile *file_sf;       
        TH2F *miniIsoSF;

        miniIsoMuScaleFactors(string year)
        {
	  TString fname;
	  TString hname;
	  if(year =="2016"){
	    fname = "data/scale_factor/TnP_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta_16.root";
	    hname = "SF";
	  }
	  else{
	    fname = "data/scale_factor/SFmuon_17.root";
	    hname = "TnP_MC_NUM_MiniIso02Cut_DEN_MediumID_PAR_pt_eta";
	  }
	  file_sf = new  TFile(fname);
	  miniIsoSF =   (TH2F*)file_sf->Get(hname);
          
       
        }
        ~miniIsoMuScaleFactors()
        {
	  delete miniIsoSF;
	  file_sf->Close();                                                                                                                                                                               
	  
        }
        //get the trigger eff per AK8 jet
        float getminiIsoScaleFactors(float pt, float eta) 
        {
	  if( pt > miniIsoSF->GetXaxis()->GetXmax() * 0.999 ) {
                    pt = miniIsoSF->GetXaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_y = miniIsoSF->GetYaxis()->FindFixBin(fabs(eta));
            int bin_index_x = miniIsoSF->GetXaxis()->FindFixBin(pt);
            
            int nbin_x = miniIsoSF->GetNbinsX();
            int nbin_y = miniIsoSF->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
	      result = miniIsoSF->GetBinContent(bin_index_x, bin_index_y);
	    }  
 
            return result;
        }
};
class MuTrigScaleFactors
{
    public: 
        TFile *file_sf1;       
        TH2F *trigSF1; //hname1 for f1
	TH2F *trigSF2;//hname2 for f1

	TFile *file_sf2;
        TH2F *trigSF3; ////hname1 for f2
	TH2F *trigSF4;//hname2 for f2 

	TString fname1;
	TString fname2;
	TString hname1;
	TString hname2;
        MuTrigScaleFactors(string year)
        {
	  
	  if(year =="2016"){
	    fname1 = "data/scale_factor/MuonTrigEfficienciesAndSF_Period4_2016.root";
	    fname2 = "data/scale_factor/MuonTrigEfficienciesAndSF_RunBtoF_2016.root";
            
	    hname1 = "IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio";
	    hname2 = "Mu50_OR_TkMu50_PtEtaBins/pt_abseta_ratio";
	  }
	  else{
	    if(year =="2017"){
	      fname1 = "data/scale_factor/MuonTrigEfficienciesAndSF_RunBtoF_Nov17.root";
	      fname2="";

	      hname1 = "IsoMu27_PtEtaBins/pt_abseta_ratio";
	      hname2="Mu50_PtEtaBins/pt_abseta_ratio";
	    }
	    else{
	      fname1 = "data/scale_factor/EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root";
	      fname2 = "data/scale_factor/EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root";

	      hname1 = "IsoMu24_PtEtaBins/pt_abseta_ratio";
	      hname2 = "Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins/pt_abseta_ratio";
	    }
	  }
	  file_sf1 = new  TFile(fname1);
	  trigSF1 =   (TH2F*)file_sf1->Get(hname1);
	  trigSF2 =   (TH2F*)file_sf1->Get(hname2);
          if(fname2!=""){
	    file_sf2 = new  TFile(fname2);
	    trigSF3 =   (TH2F*)file_sf2->Get(hname1);
	    trigSF4 =   (TH2F*)file_sf2->Get(hname2);
	  }
       
        }
        ~MuTrigScaleFactors()
        {
	  delete trigSF1;
	  delete trigSF2;
	  delete trigSF3;
	  delete trigSF4;
	  file_sf1->Close();
	  if(fname2!="") file_sf2->Close();
        }
	float getBinValue(TH2F *h2f, float pt, float eta){
	  
	  if( pt > h2f->GetXaxis()->GetXmax() * 0.999 ) {
                    pt = h2f->GetXaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_y = h2f->GetYaxis()->FindFixBin(fabs(eta));
            int bin_index_x = h2f->GetXaxis()->FindFixBin(pt);
            
            int nbin_x = h2f->GetNbinsX();
            int nbin_y = h2f->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
	      result = h2f->GetBinContent(bin_index_x, bin_index_y);
	    }  
 
            return result;
	}
        //get the trigger eff per AK8 jet
        float getTrigScaleFactors(float pt, float eta, TString year, int whichHLT) 
        {
	  float result =1.0;
	  float sf_f1 =1.0; // sf from f1
	  float sf_f2 =1.0; //sf from f2
	  if(whichHLT==0)return result;

	  if(whichHLT ==1){ //1: IsoMu24/27 ; 2: Mu50
	    sf_f1 = getBinValue(trigSF1, pt, eta);}
	  else {sf_f1 = getBinValue(trigSF2, pt, eta);}
	  if(fname2!=""){
	    if(whichHLT ==1){
	      sf_f2 = getBinValue(trigSF3,pt, eta);}
	    else{ sf_f2 = getBinValue(trigSF4, pt, eta);}
	  }
	  if(year =="2016"){
	    result = (16578.*sf_f1+20232.*sf_f2)/(16578.+20232.);// lumi weighted
	  }
	  else{
	    if(year =="2017"){result = sf_f1;}
	    else{
	      result = (50789.75*sf_f1+8950.82*sf_f2)/(50789.75+8950.82); // lumi weighted
	    }
	  }
	  //cout<<pt<<", "<<eta<<", "<<whichHLT<<", "<<year<<", "<<result<<", "<<sf_f1<<", "<<sf_f2<<"\n";

	  return result;
        }
};

class EleTrigScaleFactors
{
    public: 
        TFile *file_sf;       
        TH2F *SF;

        EleTrigScaleFactors(string year)
        {
	  TString fname = "data/scale_factor/sf_ele_"+year+"_trig_v5.root";
	  file_sf = new  TFile(fname);
	  TString hname = "EGamma_SF2D";
	  SF =   (TH2F*)file_sf->Get(hname);
          
       
        }
        ~EleTrigScaleFactors()
        {
	  delete SF;
	  file_sf->Close();                                                                                                                                                                               
	  
        }
        //get the trigger eff per AK8 jet
        float getScaleFactors(float pt, float eta) 
        {
	  if( pt > SF->GetYaxis()->GetXmax() * 0.999 ) {
                    pt = SF->GetYaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_x = SF->GetXaxis()->FindFixBin(eta);
            int bin_index_y = SF->GetYaxis()->FindFixBin(pt);
            
            int nbin_x = SF->GetNbinsX();
            int nbin_y = SF->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
	      result = SF->GetBinContent(bin_index_x, bin_index_y);
	    }  
	    //cout<<pt<<", "<<eta<<", "<<result<<"\n";
            return result;
        }
};

//#ifndef __CINT__
//// Scale factors tools
//extern TTJetsScaleFactors toptag_sf; 
//#endif

#endif
