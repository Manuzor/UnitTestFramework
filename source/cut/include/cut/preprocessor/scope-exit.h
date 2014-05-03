#pragma once

namespace cut
{
    template<typename T>
    struct ScopeExit_tpl
    {
        T m_onExitFunction;

        ScopeExit_tpl() : m_onExitFunction(nullptr) {}
        ~ScopeExit_tpl() { if(m_onExitFunction) m_onExitFunction(); }
    };

    typedef ScopeExit_tpl< ::std::function<void()> > ScopeExit;
}

// Executes code when the current scope exits. Use within a scope only!
// Example:
// CUT_SCOPE_EXIT
// {
//     printf("You will always see me when the current scope exits!\n");
// }; // <- mind the semicolon!
#define CUT_SCOPE_EXIT ::cut::ScopeExit CUT_CONCAT(scopeExit_, CUT_SOURCE_LINE) ; CUT_CONCAT(scopeExit_, CUT_SOURCE_LINE).m_onExitFunction = [&]()
