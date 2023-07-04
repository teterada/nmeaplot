#include <iomanip>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
using namespace std;

int hhmmss(int sttime, int day){
    int hour, min, sec, t;
    hour = sttime/ 10000;
    min = (sttime - hour * 10000 ) /100;
    sec = sttime - hour * 10000 - min * 100;
    t =( (  hour * 60) + min) * 60 + sec + day     * 24 * 3600 + (365*27+318)*3600*24;
    return t;
}

int main(int argc, char *argv[]){
	
    if(argc !=4){
        cout << "Usage: " << argv[0] << " [input file(NMEA converted)] [filename] [outdir]" << endl;
        exit(-1);
    }

    string ifname (argv[1]);
    string name   (argv[2]);
    string outdir (argv[3]);

    string hold,Message,gom;

    
    ifstream ifs(ifname);
   
    string ofname = outdir + "sat2" +  name;
    ofstream ofs(ofname);

	float f_time, f_time_b;
	int raw=0;
	int jump,sttime,day,n_raw,n_sat,n_scan, n;
	int t, prn, cn0, elev, azim, fix, sat, sys;
	int fix_list[5][12];

    day = 0;
    int err = 0;
    
    //ifname = "ssdraid/GPS/data/nmea/sat_SEPT0" + to_string(k) + "0.231";

	while(!ifs.eof()){
		ifs >> Message;
       // cout << Message << endl;

        if(Message == "NOS"){
            
            for(int i=0;i<5;i++){
                for(int j=0;j<12;j++){
                    fix_list[i][j] = 0;
                }
            }

            ifs >> f_time;
            sttime = f_time;
            //cout << sttime << endl;
            if(f_time_b > f_time){
                day ++;
            }
            
            t = hhmmss(sttime, day);
            f_time_b = f_time;


        }else if(Message == "GSA"){
                ifs >>sys;
                if(sys != 4){
                    if(sys == 5){ sys = 4;}
                    getline(ifs,gom,',');
                    getline(ifs,gom,',');
                        
                    getline(ifs,hold,',');
                    n =0;
                    while(hold!= "" &&  n < 12){
                        //cout << sys << " " << n  << " " << hold<< endl;
                        if(hold!= ""){
                        fix_list[sys][n] = stoi(hold);}
                        n++;
                        getline(ifs,hold,',');
                    }
                }
                    
        }else{
            if(Message == "GPGSV"){
                sat =0;
            }else if(Message == "GLGSV"){
                sat =1;
            }else if(Message == "GAGSV"){
                sat =2;
            }else if(Message == "GBGSV"){
                sat =3;
            }else if(Message == "GQGSV"){
                sat =4;
            }

            getline(ifs,hold,',');
            if(hold!=""){
            n_raw = stoi(hold);}
            getline(ifs,hold,',');
            if(hold!=""){
            raw = stoi(hold);}
            getline(ifs,hold,',');
            if(hold!=""){
            n_sat = stoi(hold);}
            if(raw == n_raw){
                n_scan = n_sat %4;
                if(n_scan == 0){
                    n_scan = 4;
                }
            }else{
                n_scan = 4;
            }
            for(int i=0;i<n_scan;i++){
                getline(ifs,hold,',');
                if(hold!=""){
                prn = stoi(hold);}
                //fix matching
                fix = 0;
                for(int i = 0 ;i<12;i++){
                    if(prn ==fix_list[sat][i]){
                        fix = 1;
                    }
                }
                
                getline(ifs,hold,',');
                if(hold == ""){
                    elev = 1000;
                }else{
                    elev = stoi(hold);
                
                }
                getline(ifs,hold,',');
                if(hold == ""){
                    azim = 1000;
                }else{
                    azim = stoi(hold);
                }

                if(i==n_scan-1){
                    getline(ifs,hold,'*');
                }else{
                    getline(ifs,hold,',');
                }
                if(hold == ""){
                    cn0 = 0;
                }else{
                    //try{
                        cn0 = stoi(hold);
                    //}
                    //catch(const invalid_argument& e){
                    //    cout << "invalid" << endl;
                    //}
                }
                //if(sttime == 235941 && sat == 4 && i==3){
                //    err = 1;}
                ofs << t << " " << sat << " " << prn << " " << elev << " " << azim << " " << cn0 << " " << fix << endl;

            }
        }
                //if(sttime == 235941 && sat == 4 && err==1){
                //    getline(ifs,gom);
                //    err=0;}
        getline(ifs,gom);
        
    }
}
