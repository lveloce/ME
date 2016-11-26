#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <string>

class TH3F;

class Interp3D {

 public:
  struct VetoInterp {
    std::vector<std::pair<double,double>> xRange;
    std::vector<std::pair<double,double>> yRange;
  };
  
  Interp3D() { m_NoInterp.clear(); m_debug = false; };
  Interp3D(std::map<std::string,VetoInterp> noInterp) { m_NoInterp = noInterp; };
  ~Interp3D() {};

  double Interpol3d(double x,double y,double z, std::shared_ptr<TH3F> h);
  void debug(bool debug = true) { m_debug = debug; };
  
 private:
  std::map<std::string,VetoInterp> m_NoInterp;
  bool m_debug;

};

