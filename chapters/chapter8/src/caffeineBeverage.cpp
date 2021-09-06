/* *********************************************
* This example implements the TEMPLATE METHOD
* design pattern, which defines the skeleton of 
* an algorithm in a method, deferring some steps
* to subclases. Template Method lets subclasses 
* redefine certain steps of an algortith without 
* changing the algorithms's structure.
********************************************* */

#include <iostream>
#include <string>

class CaffeineBeverageWithHook
{
    public:

    virtual ~CaffeineBeverageWithHook() = default;

    virtual void prepareRecipe() final
    {
        boilWater();
        brew();
        pourInCup();
        if(customerWantsCondiments())
        {
            addCondiments();
        }
    }

    private:

    virtual void brew() = 0;

    virtual void addCondiments() = 0;

    void boilWater()
    {
        std::cout << "Boiling water" << std::endl;
    }

    void pourInCup()
    {
        std::cout << "Pouring into cup" << std::endl;
    }

    virtual bool customerWantsCondiments()
    {
        return true;
    }
};

class Tea : public CaffeineBeverageWithHook
{
    public:

    private:
     
    void brew() override
    {
        std::cout << "Steeping the tea" << std::endl;
    }

    void addCondiments() override
    {
        std::cout << "Adding lemon" << std::endl;
    }
};


class CoffeeWithHook : public CaffeineBeverageWithHook
{
    public:

    private:

    bool customerWantsCondiments() override
    {
        std::string answer;

        std::cout << "Would you like milk and sugar with your coffee (y/n)" << std::endl;;
        std::cin >> answer;

        return answer == "y";
    }
     
    void brew() override
    {
        std::cout << "Dripping coffee through filter" << std::endl;
    }

    void addCondiments() override
    {
        std::cout << "Adding sugar and milk" << std::endl;
    }
};

int main()
{
    CoffeeWithHook coffee;
    Tea tea;

    std::cout << "Making coffee" << std::endl;
    coffee.prepareRecipe();
    
    std::cout << "---------------------------" << std::endl;
    
    std::cout << "Making tea" << std::endl;
    tea.prepareRecipe();
}