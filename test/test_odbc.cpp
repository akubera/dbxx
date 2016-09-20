
#include <dbxx/dbxx.hpp>
#include <dbxx/odbc/odbc.hpp>
#include <bandit/bandit.h>

using namespace bandit;


go_bandit([](){
    describe("odbc:", [](){

      it("starts in clean mode", [&](){
        float a = 1.0;
        AssertThat(a, Equals(1.0));
      });

    });
});


int main(int argc, char* argv[])
{
  return bandit::run(argc, argv);
}
