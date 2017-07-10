// +++ -------------------------------------------------------------------------
#ifndef _address_jtenv_hpp_
#define _address_jtenv_hpp_
// +++ -------------------------------------------------------------------------
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv
{
  class AddressC
  {
    public:
      AddressC (const std::string& aAddress);
      AddressC (const std::string& aWsName,
                const std::string& aProjName);

      std::string GetPath () const;

    protected:
      std::string m_wsName;
      std::string m_projName;

  };
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // _address_jtenv_hpp_
// +++ -------------------------------------------------------------------------
