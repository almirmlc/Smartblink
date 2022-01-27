#include "gui.h"

Gui::Gui(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    m_leds = new Gpio(this);
    m_state = 0;
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle);
    m_timer->start(TIMEOUT);
}


void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value);
}


void Gui::on_blinkButton_clicked()
{
    m_blink_lauf = 1;
}


void Gui::on_lauflichtButton_clicked()
{
    m_blink_lauf = 0;
    zaehler = 1;
}


void Gui::toggle()
{
    m_state = !m_state;

    if(m_blink_lauf == 1)
        {
            if(m_state == 1)
            {
                zaehler = 15;

            }else {
                zaehler = 0;
            }

                m_leds->set(zaehler);
            }

        if(m_blink_lauf == 0)
        {
            m_leds->set(zaehler);
                if(zaehler < 8)
                    {
                        zaehler = zaehler * 2;
                    }
                else {
                        zaehler = 1;
                    }
        }
}
