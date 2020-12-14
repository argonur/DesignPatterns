/* *********************************************
* This example implements the ABSTRACT FACTORY
* design pattern. This pattern provides an interface
* for creating families of related or dependent objets
* without speifying their concrete classes.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <list>

class Dough
{
    public:

    virtual ~Dough() = default;
};

class ThickCrustDough : public Dough
{

};

class ThinCrustDough : public Dough
{

};

class Sauce
{
    public:

    virtual ~Sauce() = default;

};

class PlumTomatoSauce : public Sauce
{

};

class MarinaraSauce : public Sauce
{
    
};

class Cheese
{
    public:

    virtual ~Cheese() = default;

};

class MozzarellaCheese : public Cheese
{

};

class ReggianoCheese : public Cheese
{

};

class Pepperoni
{
    public:

    virtual ~Pepperoni() = default;

};

class SlicedPepperoni : public Pepperoni
{

};

class Clams
{
    public:

    virtual ~Clams() = default;

};

class FrozenClams : public Clams
{

};

class FreshClams : public Clams
{

};

class Veggie
{
    public:

    virtual ~Veggie() = default;
};

class Onion : public Veggie
{

};

class Garlic : public Veggie
{
    
};

class Mushroom : public Veggie
{
    
};

class RedPepper : public Veggie
{
    
};

class EggPlant : public Veggie
{
    
};

class BlackOlives : public Veggie
{
    
};

class Spinach : public Veggie
{
    
};

class PizzaIngredientFactory
{
    public:

    virtual ~PizzaIngredientFactory() = default;

    virtual std::shared_ptr<Dough> createDough() = 0;
    virtual std::shared_ptr<Sauce> createSauce() = 0;
    virtual std::shared_ptr<Cheese> createCheese() = 0;
    virtual std::list<std::shared_ptr<Veggie>> createVeggies() = 0;
    virtual std::shared_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::shared_ptr<Clams> createClams() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
    public:

    std::shared_ptr<Dough> createDough() override
    {
        return std::make_shared<ThinCrustDough>();
    }
    
    std::shared_ptr<Sauce> createSauce() override
    {
        return std::make_shared<MarinaraSauce>();
    }

    std::shared_ptr<Cheese> createCheese() override
    {
        return std::make_shared<ReggianoCheese>();
    }
    
    std::list<std::shared_ptr<Veggie>> createVeggies() override
    {
        std::list<std::shared_ptr<Veggie>> veggies = {std::make_shared<Garlic>(), std::make_shared<Onion>(), 
                                                      std::make_shared<Mushroom>(), std::make_shared<RedPepper>()};
        return veggies;
    }
    
    std::shared_ptr<Pepperoni> createPepperoni() override
    {
        return std::make_shared<SlicedPepperoni>();
    }
    
    std::shared_ptr<Clams> createClams() override
    {
        return std::make_shared<FreshClams>();
    }
    
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
    public:

    std::shared_ptr<Dough> createDough() override
    {
        return std::make_shared<ThickCrustDough>();
    }
    
    std::shared_ptr<Sauce> createSauce() override
    {
        return std::make_shared<PlumTomatoSauce>();
    }

    std::shared_ptr<Cheese> createCheese() override
    {
        return std::make_shared<MozzarellaCheese>();
    }
    
    std::list<std::shared_ptr<Veggie>> createVeggies() override
    {
        std::list<std::shared_ptr<Veggie>> veggies = {std::make_shared<EggPlant>(), std::make_shared<Spinach>(), 
                                                      std::make_shared<BlackOlives>()};
        return veggies;
    }
    
    std::shared_ptr<Pepperoni> createPepperoni() override
    {
        return std::make_shared<SlicedPepperoni>();
    }
    
    std::shared_ptr<Clams> createClams() override
    {
        return std::make_shared<FrozenClams>();
    }
    
};

class Pizza
{
    private:

    std::string m_name = "";

    protected:

    std::shared_ptr<Dough> m_dough = nullptr;
    std::shared_ptr<Sauce> m_sauce = nullptr;
    std::shared_ptr<Cheese> m_cheese = nullptr;
    std::shared_ptr<Pepperoni> m_pepperoni = nullptr;
    std::shared_ptr<Clams> m_clams = nullptr;
    std::list<std::shared_ptr<Veggie>> m_veggies = {};

    public:

    virtual ~Pizza() = default;

    virtual void prepare() = 0;

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

    void setName(std::string name)
    {
        m_name = name;
    }

    std::string getName() const
    {
        return m_name;
    }

};

class CheesePizza : public Pizza
{
    private:
    
    std::shared_ptr<PizzaIngredientFactory> m_ingredientFactory;

    public:

    CheesePizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory) :
                m_ingredientFactory(ingredientFactory)
    {

    }

    void prepare() override
    {
        std::cout << "Preparing " << getName() << std::endl;
        m_dough = m_ingredientFactory->createDough();
        m_sauce = m_ingredientFactory->createSauce();
        m_cheese = m_ingredientFactory->createCheese();
    }

};

class VeggiePizza : public Pizza
{
    private:
    
    std::shared_ptr<PizzaIngredientFactory> m_ingredientFactory;

    public:

    VeggiePizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory) :
                m_ingredientFactory(ingredientFactory)
    {

    }

    void prepare() override
    {
        std::cout << "Preparing " << getName() << std::endl;
        m_dough = m_ingredientFactory->createDough();
        m_sauce = m_ingredientFactory->createSauce();
        m_cheese = m_ingredientFactory->createCheese();
        m_veggies = m_ingredientFactory->createVeggies();
    }

};

class ClamPizza : public Pizza
{
    private:
    
    std::shared_ptr<PizzaIngredientFactory> m_ingredientFactory;

    public:

    ClamPizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory) :
                m_ingredientFactory(ingredientFactory)
    {

    }

    void prepare() override
    {
        std::cout << "Preparing " << getName() << std::endl;
        m_dough = m_ingredientFactory->createDough();
        m_sauce = m_ingredientFactory->createSauce();
        m_cheese = m_ingredientFactory->createCheese();
        m_clams = m_ingredientFactory->createClams();
    }

};

class PepperoniPizza : public Pizza
{
    private:
    
    std::shared_ptr<PizzaIngredientFactory> m_ingredientFactory;

    public:

    PepperoniPizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory) :
                m_ingredientFactory(ingredientFactory)
    {

    }

    void prepare() override
    {
        std::cout << "Preparing " << getName() << std::endl;
        m_dough = m_ingredientFactory->createDough();
        m_sauce = m_ingredientFactory->createSauce();
        m_cheese = m_ingredientFactory->createCheese();
        m_pepperoni = m_ingredientFactory->createPepperoni();
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
        std::shared_ptr<Pizza> pizza = createPizza(pizzaType);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NYStylePizzaStore : public PizzaStore
{
    std::shared_ptr<Pizza> createPizza(std::string pizzaType) override
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        std::shared_ptr<PizzaIngredientFactory> ingredientFactory = std::make_shared<NYPizzaIngredientFactory>();

        if(pizzaType == "cheese")
        {
            pizza = std::make_shared<CheesePizza>(ingredientFactory);
            pizza->setName("New York Style Cheese Pizza");
        }
        else if(pizzaType == "veggie")
        {
            pizza = std::make_shared<VeggiePizza>(ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");
        }
        else if(pizzaType == "clam")
        {
            pizza = std::make_shared<ClamPizza>(ingredientFactory);
            pizza->setName("New York Style Clam Pizza"); 
        }
        else if(pizzaType == "pepperoni")
        {
            pizza = std::make_shared<PepperoniPizza>(ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");            
        }
        
        return pizza;
    }
};

class ChicagoStylePizzaStore : public PizzaStore
{
    std::shared_ptr<Pizza> createPizza(std::string pizzaType) override
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        std::shared_ptr<PizzaIngredientFactory> ingredientFactory = std::make_shared<ChicagoPizzaIngredientFactory>();

        if(pizzaType == "cheese")
        {
            pizza = std::make_shared<CheesePizza>(ingredientFactory);
            pizza->setName("Chicago Style Cheese Pizza");
        }
        else if(pizzaType == "veggie")
        {
            pizza = std::make_shared<VeggiePizza>(ingredientFactory);
            pizza->setName("Chicago Style Veggie Pizza");
        }
        else if(pizzaType == "clam")
        {
            pizza = std::make_shared<ClamPizza>(ingredientFactory);
            pizza->setName("Chicago Style Clam Pizza"); 
        }
        else if(pizzaType == "pepperoni")
        {
            pizza = std::make_shared<PepperoniPizza>(ingredientFactory);
            pizza->setName("Chicago Style Pepperoni Pizza");            
        }
        
        return pizza;
    }
};

int main(void)
{
    std::shared_ptr<PizzaStore> nyPizzaStore = std::make_shared<NYStylePizzaStore>();
    nyPizzaStore->orderPizza("cheese");
    std::cout << std::endl;
    nyPizzaStore->orderPizza("veggie");
    std::cout << std::endl;
    nyPizzaStore->orderPizza("clam");
    std::cout << std::endl;
    nyPizzaStore->orderPizza("pepperoni");
    std::cout << std::endl;

    std::shared_ptr<PizzaStore> chicagoPizzaStore = std::make_shared<ChicagoStylePizzaStore>();
    chicagoPizzaStore->orderPizza("cheese");
    std::cout << std::endl;
    chicagoPizzaStore->orderPizza("veggie");
    std::cout << std::endl;
    chicagoPizzaStore->orderPizza("clam");
    std::cout << std::endl;
    chicagoPizzaStore->orderPizza("pepperoni");
    std::cout << std::endl;
}
