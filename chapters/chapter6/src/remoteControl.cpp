/* *********************************************
* This example implements the COMMAND
* design pattern, which encapsulates a request as
* an object, thereby letting you parameterize other
* objects with different requests, queue or log requests,
* and support undoable operations.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <list>

class Light
{
    protected:
    
    std::string m_location;

    public:

    Light(std::string location) : m_location(location)
    {

    }

    void on()
    {
        std::cout << m_location << " light is on" << std::endl;
    }

    void off()
    {
        std::cout << m_location << " light is off" << std::endl;
    }
};

class Stereo
{
    protected:

    std::string m_location;

    public:
    
    Stereo(std::string location) : m_location(location)
    {

    }

    void on()
    {
        std::cout << m_location << " stereo is on" << std::endl;
    }

    void off()
    {
        std::cout << m_location << " stereo is off" << std::endl;
    }

    void setRadio()
    {
        std::cout << m_location << " has the radio set" << std::endl;        
    }

    void setVolume(uint volume)
    {
        std::cout << m_location << " has volume set to " << std::to_string(volume) << std::endl;
    }

};

class SecurityControl
{
    public:

    void arm()
    {
        std::cout << "SecurityControl is armed" << std::endl;
    }

    void disarm()
    {
        std::cout << "Security Control is disarmed" << std::endl;
    }
};

class Sprinkler
{
    public:

    void waterOn()
    {
        std::cout << "Sprinkler is on" << std::endl;
    }

    void waterOff()
    {
        std::cout << "Sprinkler is off" << std::endl;
    }
};

class Command  
{
    public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class LightOnCommand : public Command
{
    private:

    std::shared_ptr<Light> m_light;

    public:

    LightOnCommand(std::shared_ptr<Light> light) : m_light(light)
    {

    }

    void execute() override
    {
        m_light->on();
    }

    void undo() override
    {
        m_light->off();
    }
};

class LightOffCommand : public Command
{
    private:

    std::shared_ptr<Light> m_light;

    public:

    LightOffCommand(std::shared_ptr<Light> light) : m_light(light)
    {

    }

    void execute() override
    {
        m_light->off();
    }

    void undo() override
    {
        m_light->on();
    }
};

class StereoOnWithRadioCommand : public Command
{
    private:

    std::shared_ptr<Stereo> m_stereo;

    public:

    StereoOnWithRadioCommand(std::shared_ptr<Stereo> stereo) : m_stereo(stereo)
    {

    }

    void execute() override
    {
        m_stereo->on();
        m_stereo->setRadio();
        m_stereo->setVolume(10);
    }

    void undo() override
    {
        m_stereo->off();;
    }
};

class StereoOffCommand : public Command
{
    private:

    std::shared_ptr<Stereo> m_stereo;

    public:

    StereoOffCommand(std::shared_ptr<Stereo> stereo) : m_stereo(stereo)
    {

    }

    void execute() override
    {
        m_stereo->off();
    }

    void undo() override
    {
        m_stereo->on();
        m_stereo->setRadio();
        m_stereo->setVolume(10);
    }
};

class SecurityControlArmCommand : public Command
{
    private:

    std::shared_ptr<SecurityControl> m_securityControl;

    public:

    SecurityControlArmCommand( std::shared_ptr<SecurityControl> securityControl) : m_securityControl(securityControl)
    {

    }

    void execute() override
    {
        m_securityControl->arm();
    }

    void undo() override
    {
        m_securityControl->disarm();
    }
};

class SecurityControlDisarmCommand : public Command
{
    private:

    std::shared_ptr<SecurityControl> m_securityControl;

    public:

    SecurityControlDisarmCommand(std::shared_ptr<SecurityControl> securityControl) : m_securityControl(securityControl)
    {

    }

    void execute() override
    {
        m_securityControl->disarm();
    }

    void undo() override
    {
        m_securityControl->arm();
    }
};

class SprinklerOnCommand : public Command
{
    private:

    std::shared_ptr<Sprinkler> m_sprinkler;

    public:

    SprinklerOnCommand(std::shared_ptr<Sprinkler> sprinkler) : m_sprinkler(sprinkler)
    {

    }

    void execute() override
    {
        m_sprinkler->waterOn();
    }

    void undo() override
    {
        m_sprinkler->waterOff();
    }
};

class SprinklerOffCommand : public Command
{
    private:

    std::shared_ptr<Sprinkler> m_sprinkler;

    public:

    SprinklerOffCommand(std::shared_ptr<Sprinkler> sprinkler) : m_sprinkler(sprinkler)
    {

    }

    void execute() override
    {
        m_sprinkler->waterOff();
    }

    void undo() override
    {
        m_sprinkler->waterOn();
    }
};

class NoCommand : public Command
{
    public:

    void execute() override
    {
        std::cout << "No command assigned" << std::endl;
    }

    void undo() override
    {
        std::cout << "No command assigned" << std::endl;
    }


};

class MacroCommand : public Command
{
    private:

    std::list<std::shared_ptr<Command>> m_commands;

    public:

    MacroCommand(std::list<std::shared_ptr<Command>>& commands) : m_commands(commands)
    {

    }

    void execute() override
    {
        std::cout << "------------- Macro execute -------------" << std::endl; 
        for(auto command : m_commands)
        {
            command->execute();
        }
    }

    void undo() override
    {
        std::cout << "------------- Macro undo -------------" << std::endl; 
        for(auto command : m_commands)
        {
            command->undo();
        }
    }
};

class RemoteControl
{
    private:

    static constexpr uint numberOfSlots = 7;
    std::shared_ptr<Command> m_onCommands[numberOfSlots] = {nullptr};
    std::shared_ptr<Command> m_offCommands[numberOfSlots] = {nullptr};
    std::shared_ptr<Command> m_undoCommand = nullptr;

    public:

    RemoteControl()
    {
        std::shared_ptr<Command> noCommand = std::make_shared<NoCommand>();
        for(uint i = 0; i < numberOfSlots; i++)
        {
            m_onCommands[i] = noCommand;
            m_offCommands[i] = noCommand;
        }
        m_undoCommand = noCommand;
    }

    void setCommand(uint slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
    {
        if(slot < 7)
        {
            m_onCommands[slot] = onCommand;
            m_offCommands[slot] = offCommand;
        }
        else
        {
            std::cout << "Use slots from 0 to 6" << std::endl;
        }
    }

    void onButtonWasPushed(uint slot)
    {
        m_onCommands[slot]->execute();
        m_undoCommand = m_onCommands[slot];
    }

    void offButtonWasPushed(uint slot)
    {
        m_offCommands[slot]->execute();
        m_undoCommand = m_offCommands[slot];
    }

    void undoButtonWasPushed()
    {
        m_undoCommand->undo();
    }
};

int main()
{
    std::unique_ptr<RemoteControl> remoteControl = std::make_unique<RemoteControl>();

    std::shared_ptr<Light> livingRoomLight = std::make_shared<Light>("LivingRoom");
    std::shared_ptr<Light> kitchenLight = std::make_shared<Light>("Kitchen");
    std::shared_ptr<Stereo> stereo = std::make_shared<Stereo>("Living Room");
    std::shared_ptr<Sprinkler> sprinkler = std::make_shared<Sprinkler>();
    std::shared_ptr<SecurityControl> securityControl = std::make_shared<SecurityControl>();

    std::shared_ptr<LightOnCommand> livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    std::shared_ptr<LightOffCommand> livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    std::shared_ptr<LightOnCommand> kitchenLightOn = std::make_shared<LightOnCommand>(kitchenLight);
    std::shared_ptr<LightOffCommand> kitchenLightOff = std::make_shared<LightOffCommand>(kitchenLight);
    std::shared_ptr<StereoOnWithRadioCommand> stereoOn = std::make_shared<StereoOnWithRadioCommand>(stereo);
    std::shared_ptr<StereoOffCommand> stereoOff = std::make_shared<StereoOffCommand>(stereo);
    std::shared_ptr<SprinklerOnCommand> sprinklerOn = std::make_shared<SprinklerOnCommand>(sprinkler);
    std::shared_ptr<SprinklerOffCommand> sprinklerOff = std::make_shared<SprinklerOffCommand>(sprinkler);
    std::shared_ptr<SecurityControlArmCommand> securityControlArm = std::make_shared<SecurityControlArmCommand>(securityControl);
    std::shared_ptr<SecurityControlDisarmCommand> securityControlDisarm = std::make_shared<SecurityControlDisarmCommand>(securityControl);

    remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl->setCommand(2, stereoOn, stereoOff);
    remoteControl->setCommand(3, sprinklerOn, sprinklerOff);
    remoteControl->setCommand(4, securityControlArm, securityControlDisarm);

    std::list<std::shared_ptr<Command>> partyOn = {livingRoomLightOn, kitchenLightOn, stereoOn, sprinklerOn, securityControlArm};
    std::shared_ptr<MacroCommand> partyOnMacro = std::make_shared<MacroCommand>(partyOn);

    std::list<std::shared_ptr<Command>> partyOff = {livingRoomLightOff, kitchenLightOff, stereoOff, sprinklerOff, securityControlDisarm};
    std::shared_ptr<MacroCommand> partyOffMacro = std::make_shared<MacroCommand>(partyOff);

    remoteControl->setCommand(5, partyOnMacro, partyOffMacro);

    // Smulation
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(2);
    remoteControl->offButtonWasPushed(2);
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(3);
    remoteControl->offButtonWasPushed(3);
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(4);
    remoteControl->offButtonWasPushed(4);
    remoteControl->undoButtonWasPushed();

    // Party
    remoteControl->offButtonWasPushed(5);
    remoteControl->onButtonWasPushed(5);
    remoteControl->undoButtonWasPushed();
    std::cout << "----------------------------" << std::endl;

    // Not assigned slot
    remoteControl->onButtonWasPushed(6);
    remoteControl->offButtonWasPushed(6);
    remoteControl->undoButtonWasPushed();
}