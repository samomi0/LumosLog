#include "DummyAdapter.hpp"

class DummyModule {
 public:
  void process(int value) {
    LumosLog::log(LumosLog::LogLevel::INFO, "DummyModule", "Processing value: {}", value);
  }
};

int main() {
  DummyModule bm;
  bm.process(114514);

  /* NOT NECESSARY 
   * it could be used in your example.
   * initLumosLog() will be defined in the module to be integrated. */
  initLumosLog();
  
  bm.process(1919810);

  return 0;
}
