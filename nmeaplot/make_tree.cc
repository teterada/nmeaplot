#include "TFile.h"
#include "TTree.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;


int main(int argc, char *argv[]){
	
    
    if(argc!=2){
        cout << "Usage: " << argv[0] << "[input sat2 file]" << endl;
        exit(-1);
     }
    //string outdir (argv[2]);
    string ifname_s (argv[1]);

    
	//ifstream ifs("/home/kterada/disk03/hktm/data/20230704_hk_rdnhuttest/20230704_2.txt");
    //
	//ifstream ifs(input);
    
    //read sat. file
    ifstream ifs(ifname_s);

	Int_t t, prn, cn0, elev, azim, fix, sat, sys;

    
    //string ofname = "test.root";
	TFile *file = new TFile("tree.root","recreate");
	TTree *tree = new TTree("tree","tree");

	tree->Branch("t",&t,"t/I");
	tree->Branch("sat",&sat,"sat/I");
	tree->Branch("prn",&prn,"prn/I");
	tree->Branch("cn0",&cn0,"cn0/I");
	tree->Branch("elev",&elev,"elev/I");
	tree->Branch("azim",&azim,"azim/I");
	tree->Branch("fix",&fix,"fix/I");
	

	while(!ifs.eof()){
		ifs >> t >> sat >> prn >> elev >> azim >> cn0 >> fix;
        cout << t << endl;
        tree->Fill();

            
    }
	tree->Write();

    
    cout << "writed" << endl;

    file->Close();
    cout << "closed" << endl;
    return 0;
}
