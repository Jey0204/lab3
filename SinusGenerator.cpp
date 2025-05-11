#define _USE_MATH_DEFINES
#include "SinusGenerator.h"

SinusGenerator::SinusGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda), m_czestotliwosc(czestotliwosc)
{

    m_omega = 2.0 * M_PI * m_czestotliwosc;

    m_x1 = 0.0;
    m_x2 = m_amplituda * sin(m_omega);
}

double SinusGenerator::generuj()
{

    double result = m_x1;

    double xNew = 2.0 * cos(m_omega) * m_x2 - m_x1;

    m_x1 = m_x2;
    m_x2 = xNew;

    return result * m_amplituda + SygnalDekorator::generuj();
}

void SinusGenerator::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_amplituda << std::endl;
    os << m_czestotliwosc << std::endl;
    os << m_x1 << std::endl;
    os << m_x2 << std::endl;
    if (m_dekorowanySygnal)
    {
        m_dekorowanySygnal->zapisz(os);
    }
    else
    {
        os << "NULL" << std::endl;
    }
}
