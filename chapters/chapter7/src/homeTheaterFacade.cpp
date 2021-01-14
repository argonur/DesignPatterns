/* *********************************************
* This example implements the FACADE
* design pattern, which provides a unified interface 
* to a set of interfaces in a subsystem. Facade 
* defines a higher level interface that makes 
* the subsystem easier to use.
********************************************* */

#include <iostream>
#include <string>

class Tuner
{
    private:

    public:
    
    void on()
    {}
    
    void off()
    {}

    void setAmpflifier()
    {}

    void setFm()
    {}

    void setFrecuency()
    {}
};

class DvdPlayer
{
    private:

    public:
    
    void on()
    {
        std::cout << "DVD player on" << std::endl; 
    }

    void off()
    {
        std::cout << "DVD player off" << std::endl; 
    }

    void play()
    {
        std::cout << "Playing DVD" << std::endl; 
    }

    void pause()
    {
        std::cout << "DVD paused" << std::endl;
    }

    void eject()
    {
        std::cout << "Ejecting DVD" << std::endl;
    }

    void stop()
    {
        std::cout << "DVD stopped" << std::endl;
    }        
};

class CdPlayer
{
    private:

    public:
    
    void on()
    {}
    
    void off()
    {}
};

class Amplifier
{
    private:

    public:

    void on()
    {
        std::cout << "Amplifier on" << std::endl;          
    }
    
    void off()
    {
        std::cout << "Amplifier off" << std::endl; 
    }

    void setCd()
    {

    }
    
    void setDvd()
    {
        std::cout << "Amplifier set to DVD" << std::endl; 
    }

    void setStereoSound()
    {}

    void setSorroundSound()
    {
        std::cout << "Amplifier sorround sound on (5 speakers, 1 subwoofer)" << std::endl; 
    }

    void setTuner()
    {}

    void setVolume(uint volume)
    {
        std::cout << "Amplifier volume set to " << std::to_string(volume) << std::endl; 
    }
};

class Projector
{
    private:

    public:
    
    void on()
    {
        std::cout << "Projector on" << std::endl;        
    }

    void off()
    {
        std::cout << "Projector off" << std::endl;  
    }

    void setInput(std::string input)
    {
        std::cout << "Projector input set to " << input << std::endl;
    }

    void wideScreenMode()
    {
        std::cout << "Projector in widescreen mode (16x9 aspect ratio)" << std::endl;          
    }    
};

class TheaterLights
{
    private:

    public:
    
    void on()
    {
        std::cout << "Theater lights on" << std::endl;
    }

    void off()
    {
        std::cout << "Theater lights off" << std::endl;
    }

    void dim(uint level)
    {
        std::cout << "Dimming lights to " << std::to_string(level) << "%" << std::endl;
    }    
};

class PopcornPopper
{
    private:

    public:
    
    void on()
    {
        std::cout << "Popcorn popper on" << std::endl;
    }

    void off()
    {
        std::cout << "Popcorn popper off" << std::endl;
    }

    void pop()
    {
        std::cout << "Popcorn popper popping popcorns!" << std::endl;
    }
};

class Screen
{
    private:

    public:
    
    void up()
    {
        std::cout << "Theater screen going up" << std::endl;
    }

    void down()
    {
        std::cout << "Theater screen going down" << std::endl;
    }
};

class HomeTheaterFacade
{
    private:

    Amplifier m_amplifier;
    Tuner m_tuner;
    DvdPlayer m_dvdPlayer;
    CdPlayer m_cdPlayer;
    Projector m_projector;
    TheaterLights m_theaterLights;
    Screen m_screen;
    PopcornPopper m_popcornPopper;

    public:

    HomeTheaterFacade(Amplifier& amplifier, Tuner& tuner, DvdPlayer& dvdPlayer, CdPlayer& cdPlayer, Projector& projector, TheaterLights& theaterLights, Screen& screen, PopcornPopper& popcornPopper) :
                    m_amplifier(amplifier), m_tuner(tuner), m_dvdPlayer(dvdPlayer), m_cdPlayer(cdPlayer), m_projector(projector), m_theaterLights(theaterLights), m_screen(screen), m_popcornPopper(popcornPopper)
    {

    }

    void watchMovie()
    {
        std::cout << "Get ready to watch a movie..." << std::endl;

        m_popcornPopper.on();
        m_popcornPopper.pop();
        m_theaterLights.dim(10);
        m_screen.down();
        m_projector.on();
        m_projector.setInput("DVD");
        m_projector.wideScreenMode();
        m_amplifier.on();
        m_amplifier.setDvd();
        m_amplifier.setVolume(5);
        m_dvdPlayer.on();
        m_dvdPlayer.play();

        std::cout << std::endl;
    }

    void endMovie()
    {
        std::cout << "Shutting movie theater down..." << std::endl;

        m_popcornPopper.off();
        m_theaterLights.on();
        m_screen.up();
        m_projector.off();
        m_amplifier.off();
        m_dvdPlayer.stop();
        m_dvdPlayer.eject();
        m_dvdPlayer.off();

        std::cout << std::endl;
    }

};

int main()
{
    Amplifier amplifier;
    Tuner tuner; 
    DvdPlayer dvdPlayer; 
    CdPlayer cdPlayer; 
    Projector projector; 
    TheaterLights theaterLights; 
    Screen screen; 
    PopcornPopper popcornPopper;

    HomeTheaterFacade homeTheater(amplifier, tuner, dvdPlayer, cdPlayer, projector, theaterLights, screen, popcornPopper);

    homeTheater.watchMovie();
    homeTheater.endMovie();
}
