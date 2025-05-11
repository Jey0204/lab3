#include "TrojkatGenerator.h"
#include <cmath>     // For fmod, fabs
#include <algorithm> // For std::min, std::max if needed

TrojkatGenerator::TrojkatGenerator(SygnalGenerator *dekorowanySygnal, double amplituda, double czestotliwosc, double wypelnienie)
    : SygnalDekorator(dekorowanySygnal), m_amplituda(amplituda), m_czestotliwosc(czestotliwosc), m_wypelnienie(wypelnienie), m_czas(0.0)
{
    if (m_czestotliwosc > 0)
    {
        m_okres = 1.0 / m_czestotliwosc;
    }
    else
    {
        m_okres = 0.0;
    }
    if (m_wypelnienie <= 0.0 || m_wypelnienie >= 1.0)
    {
        m_wypelnienie = 0.5;
    }
}

double TrojkatGenerator::generuj()
{
    double wartoscGenerowana = 0.0;
    if (m_okres > 0.0)
    {
        double czasWOkresie = fmod(m_czas, m_okres);
        double punktSzczytu = m_wypelnienie * m_okres;

        if (czasWOkresie < punktSzczytu)
        {
            if (punktSzczytu > 0)
                wartoscGenerowana = (czasWOkresie / punktSzczytu) * 2.0 - 1.0;
            else
                wartoscGenerowana = -1.0;
        }
        else
        {
            if (m_okres - punktSzczytu > 0)
                wartoscGenerowana = ((m_okres - czasWOkresie) / (m_okres - punktSzczytu)) * 2.0 - 1.0;
            else
                wartoscGenerowana = -1.0;
        }
        wartoscGenerowana *= m_amplituda;
        m_czas += 1.0;
    }
    else
    {
        wartoscGenerowana = 0.0;
    }
    return wartoscGenerowana + SygnalDekorator::generuj();
}

void TrojkatGenerator::zapisz(std::ostream &os) const
{
    os << getType() << std::endl;
    os << m_amplituda << std::endl;
    os << m_czestotliwosc << std::endl;
    os << m_wypelnienie << std::endl;
    os << m_czas << std::endl;
    if (m_dekorowanySygnal)
    {
        m_dekorowanySygnal->zapisz(os);
    }
    else
    {
        os << "NULL" << std::endl;
    }
}
