/* *********************************************
* This example implements the FACTORY METHOD
* design pattern. This pattern defines an interface
* for creating an object, but lets subclasses decide
* which class to instantiate. Factory Method lets a class
* defer instantiation to subclasses.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <list>


class Pizza
{
    private:

    std::string m_name;
    std::string m_dough;
    std::string m_sauce;
    std::list<std::string> m_toppings;

    public:

    virtual ~Pizza() = default;

    Pizza(const std::string& name, const std::string& dough, const std::string& sauce, const std::list<std::string>& toppings) :
        m_name(name), m_dough(dough), m_sauce(sauce), m_toppings(toppings)
    {

    }

    void prepare() const
    {
        std::cout << "Preparing " << getName() << std::endl;
        std::cout << "Tossing dough: " << m_dough << std::endl;
        std::cout << "Adding sauce: " << m_sauce << std::endl;
        std::cout << "Adding toppings:" << std::endl;
        for(auto topping : m_toppings)
        {
            std::cout << "  " << topping << std::endl;
        }
    }

    virtual void bake() const
    {
        std::cout << "Bake for 20 minutes at 200° C" << std::endl;
    }

    virtual void cut() const
    {
        std::cout << "Cut pizza in diagonal slices" << std::endl;
    }

    virtual void box() const
    {
        std::cout << "Place pizza into the box" << std::endl;
    }

    std::string getName() const
    {
        return m_name;
    }

};

class NYStyleCheesePizza : public Pizza
{
    public: 
    NYStyleCheesePizza() : Pizza("NY Style Cheese Pizza", 
                                 "Thin crust dough", 
                                 "Marinara sauce", 
                                 {"Grated Reggiano Cheese"})
    {

    }

};

class NYStyleVeggiePizza : public Pizza
{
    public: 
    NYStyleVeggiePizza() : Pizza("NY Style Veggie Pizza", 
                                 "Thin crust dough", 
                                 "Marinara sauce", 
                                 {"Paprika", "Onion", "Olives", "Champignons"})
    {

    }

};

class ChicagoStyleCheesePizza : public Pizza
{
    public: 
    ChicagoStyleCheesePizza() : Pizza("Chicago Style deep dish Cheese Pizza", 
                                    "Extra thick crust dough", 
                                    "Plum tomate sauce", 
                                    {"Shredded Mozzarella Cheese"})
    {

    }

    void cut() const override
    {
        std::cout << "Cut pizza in square slices" << std::endl;
    }

};

class ChicagoStyleVeggiePizza : public Pizza
{
    public: 
    ChicagoStyleVeggiePizza() : Pizza("Chicago Style Veggie Pizza", 
                                    "Extra thick crust dough", 
                                    "Plum tomate sauce", 
                                    {"Paprika", "Onion", "Olives", "Champignons"})
    {

    }

    void cut() const override
    {
        std::cout << "Cut pizza in square slices" << std::endl;
    }

};

class PizzaStore
{
    protected:

    virtual std::shared_ptr<Pizza> createPizza(std::string pizzaType) = 0;

    public:

    virtual ~PizzaStore() = default;

    std::shared_ptr<Pizza> orderPizza(std::string pizzaType)
    {
        std::shared_ptr<Pizza> pizza;

        pizza = createPizza(pizzaType);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NYStylePizzaStore : public PizzaStore
{
    public:

    std::shared_ptr<Pizza> createPizza(std::string pizzaType) override
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        if(pizzaType == "cheese")
        {
            pizza = std::make_shared<NYStyleCheesePizza>();
        }
        else if(pizzaType == "veggie")
        {
            pizza = std::make_shared<NYStyleVeggiePizza>();
        }
        
        return pizza;
    }
};

class ChicagoStylePizzaStore : public PizzaStore
{
    public:

    std::shared_ptr<Pizza> createPizza(std::string pizzaType) override
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        if(pizzaType == "cheese")
        {
            pizza = std::make_shared<ChicagoStyleCheesePizza>();
        }
        else if(pizzaType == "veggie")
        {
            pizza = std::make_shared<ChicagoStyleVeggiePizza>();
        }
        
        return pizza;
    }
};

int main(void)
{
    std::shared_ptr<PizzaStore> nyPizzaStore = std::make_shared<NYStylePizzaStore>();
    nyPizzaStore->orderPizza("veggie");
    std::cout << std::endl;
    nyPizzaStore->orderPizza("cheese");
    std::cout << std::endl;
    
    std::shared_ptr<PizzaStore> chicagoPizzaStore = std::make_shared<ChicagoStylePizzaStore>();
    chicagoPizzaStore->orderPizza("veggie");
    std::cout << std::endl;
    chicagoPizzaStore->orderPizza("cheese");
    std::cout << std::endl;
}
