#include "gui.h"
#include "gpio.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_state = false;
    lauflicht = false;
    m_timer = new QTimer(this);
    m_gpio = new Gpio(this);
    connect(m_timer, &QTimer::timeout, this, &Gui::onTimer);
    wundschuh = 0;

    int time = 1000 / speedSlider->value();
    m_timer->setInterval(time);
}

void Gui::onTimer()
{
    if(lauflicht == true)
    {
        m_state = !m_state;
        label->setNum(m_state);
        for(int i = 0; i < 4; i++)
        {
           m_gpio->set(LEDS[i], 0);
        }

        m_gpio->set(LEDS[wundschuh], 1);
        wundschuh++;
        if(wundschuh == 4) wundschuh = 0;
    } else {
        m_state = !m_state;
        label->setNum(m_state);
        m_gpio->set(LEDS[0], m_state);
    }
}

void Gui::on_speedSlider_valueChanged(int value)
{
    int time = 1000 / value;
    m_timer->setInterval(time);
}

void Gui::on_blinkButton_clicked()
{
    m_timer->start();
    lauflicht = false;
}

void Gui::on_lauflichtButton_clicked()
{
    m_timer->start();
    lauflicht = true;
}
