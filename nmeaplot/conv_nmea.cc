//convert NMEA format file to two file easy to understand
//one is summarized position info.
//other one is summarized gnss reception info.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
    
    if(argc !=4){
        cout << "Usage: " << argv[0] << " [input file(NMEA format)] [filename] [outdir]" << endl;
        exit(-1);
    }
    
    string ifname (argv[1]);
    string name   (argv[2]);
    string outdir (argv[3]);

    string ofname_p = outdir + "pos" + name;    
    string ofname_s = outdir + "sat" + name;
    string message, time, gom, lat, ns, lon, ew, alt, altuni, geoid, nos;


	ifstream ifs(ifname);
	ofstream ofs_p(ofname_p);
	ofstream ofs_s(ofname_s);

	int l_n; //used to distinguish sat. system (e.g. gps, glonass)
	

	while(!ifs.eof()){
		getline(ifs, message, ',');
		if(message == "$GPGGA"){
			getline(ifs,time,',');
                        getline(ifs,lat,',');
	                getline(ifs,ns,',');
        	        getline(ifs,lon,',');
                	getline(ifs,ew,',');
                	getline(ifs,gom,',');
                	getline(ifs,nos,',');
               		getline(ifs,gom,',');
                	getline(ifs,alt,',');
                	getline(ifs,altuni,',');
                	getline(ifs,geoid,',');
			ofs_p << time << " " << lat << " " << lon << " " << alt << " " << geoid << endl;
			ofs_s << "NOS " << time << " " << nos << endl;
			getline(ifs,gom);
			l_n = 0;
		}else if(message == "$GPGSA"){
			getline(ifs,gom);
			ofs_s << "GSA " << l_n << " " << gom << endl;
			l_n +=1;
		}else if(message == "$GPGSV"){
			getline(ifs,gom);
			ofs_s << "GPGSV " << gom << endl;
		}else if(message == "$GLGSV"){
			getline(ifs,gom);
			ofs_s << "GLGSV " << gom << endl;
		}else if(message == "$GAGSV"){
			getline(ifs,gom);
			ofs_s << "GAGSV " << gom << endl;
		}else if(message == "$GBGSV"){
			getline(ifs,gom);
			ofs_s << "GBGSV " << gom << endl;
		}else if(message == "$GQGSV"){
			getline(ifs,gom);
			ofs_s << "GQGSV " << gom << endl;
		}else{
			getline(ifs, gom);
		}
	}
	ofs_p.close();
	ofs_s.close();
	cout << ifname << " has been converted\n";


}
