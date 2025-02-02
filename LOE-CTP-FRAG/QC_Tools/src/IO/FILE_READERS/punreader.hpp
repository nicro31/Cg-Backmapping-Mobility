
#ifndef _CATNIP_PUNREADER_HPP_
#define _CATNIP_PUNREADER_HPP_

#include <vector>

#include "../../MATRIX/matrix.hpp"
#include "filereader.hpp"
// Gaussian fort.7/.pun file reader
namespace catnip {

class PunReader : public FileReader {
  public:
    PunReader(std::string str);     
    Matrix * getCoefsMatrix(std::string orb_type); 
    bool restrictedShell() { return coefs.size()==1; }
    
    // N. ROLLAND Try fix memory leak by adding destructor
    ~PunReader()
    {
	for(std::map<std::string,Matrix *>::iterator it=coefs.begin() ; it!=coefs.end() ; ++it)
	{	  
	    if(it->second != nullptr) {delete it->second; it->second = nullptr;}
	}
    }

  private:
    virtual void registerSections_();
    virtual void validFileName_();

    static void OrbitalCoefAlphaSectionReader(void *);
    static void OrbitalCoefBetaSectionReader(void *);

    void ReadCoef(std::string orb_type);
    std::vector<double> readGausCoefLine(std::string line);
    
    std::map<std::string,Matrix *> coefs;
};

}
#endif //  _CATNIP_PUNREADER_HPP_
