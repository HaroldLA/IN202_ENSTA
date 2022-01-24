#ifndef componentHPP
#define componentHPP

class Component
{
private:
  const char* m_Name;
  bool m_Debug;
public:
  Component(const char* theName, bool debug = false): m_Name(theName), m_Debug(debug)
  {}
  const char* name() const { return m_Name; }
  bool IsDebug() const { return m_Debug; }

  void DebugOn() { m_Debug = true; }
  void DebugOff() { m_Debug = false; }
};

#endif
