/* *********************************************
* This example implements the STRATEGY
* design pattern, which defines a family of algorithms,
* encapsulates each one, and makes them interchangable.
* Strategy lets the algorithm vary independently from
* clients that use it.
********************************************* */

#include <iostream>
#include <list>

class FlyBehavior {
    public:
        virtual ~FlyBehavior() = default;
        virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
    public:
        void fly() override{
            std::cout << "I'm flying!!" << std::endl;
        }
};

class FlyNoWay : public FlyBehavior
{
    public:
        void fly() override{
            std::cout << "I can't fly" << std::endl;
        }
};

class FlyRocketPowered : public FlyBehavior
{
    public:
        void fly() override{
            std::cout << "I'm flying with a rocket!" << std::endl;
        }
};

class QuackBehavior {
    public:
        virtual ~QuackBehavior() = default;
        virtual void quack() = 0;
};

class Quack : public QuackBehavior {
    public:
        void quack() override {
            std::cout << "Quack" << std::endl;
        }
};

class MuteQuack : public QuackBehavior {
    public:
        void quack() override {
            std::cout << "Silence" << std::endl;
        }
};

class Squeak : public QuackBehavior {
    public:
        void quack() override{
            std::cout << "Squeak" << std::endl;
        }
};

class Duck{

    public:
        Duck(FlyBehavior* fb, QuackBehavior* qb) : m_flyBehavior(fb), m_quackBehavior(qb)
        {

        }

        virtual ~Duck() {
            delete m_flyBehavior;
            delete m_quackBehavior;
        }

        Duck(const Duck&) = default;
        Duck& operator=(const Duck&) = default;

        virtual void display() = 0;

        void performFly() {
            m_flyBehavior->fly();
        };

        void performQuack() {
            m_quackBehavior->quack();
        };

        void swim() {
            std::cout << "All ducks float, even decoys!" << std::endl;
        }

        void setFlyBehavior(FlyBehavior* fb) {
            if(fb != nullptr){
                delete m_flyBehavior;
                m_flyBehavior = fb;
            }
        }

        void setQuackBehavior(QuackBehavior* qb) {
            if(qb != nullptr)
            {
                delete m_quackBehavior;
                m_quackBehavior = qb;
            }
        }

    private:
        FlyBehavior* m_flyBehavior;
        QuackBehavior* m_quackBehavior;

};

class MallardDuck : public Duck {

    public:
        MallardDuck() : Duck(new FlyWithWings, new Quack) 
        {

        }

        void display() override {
            std::cout << "I'm a mallard duck" << std::endl;
        }
};

class RedHeadDuck : public Duck {

    public:
        RedHeadDuck() : Duck(new FlyWithWings,new Quack)
        {

        }

        void display() override {
            std::cout << "I am a red head duck" << std::endl;
        }
};

class RubberDuck : public Duck {

    public:
        RubberDuck() : Duck(new FlyNoWay,new Squeak)
        {

        }

        void display() override {
            std::cout << "I am a rubber duck" << std::endl;
        }
};

class DecoyDuck : public Duck {

    public:
        DecoyDuck() : Duck(new FlyNoWay,new MuteQuack)
        {

        }

        void display() override {
            std::cout << "I am a decoy duck" << std::endl;
        }
};

class ModelDuck : public Duck {

    public:
        ModelDuck() : Duck(new FlyNoWay,new Quack)
        {

        }

        void display() override {
            std::cout << "I am a model duck" << std::endl;
        }
};

int main(void)
{
    std::cout << "chapter 1 - strategy" << std::endl;

    Duck* mallard = new MallardDuck();
    Duck* redHead = new RedHeadDuck();
    Duck* rubber = new RubberDuck();
    Duck* decoy = new DecoyDuck();
    Duck* model = new ModelDuck();

    std::list<Duck*> ducks = {mallard, redHead, rubber, decoy, model};

    for(auto duck : ducks)
    {
        duck->display();
        duck->performQuack();
        duck->performFly();
        std::cout << std::endl;
    }

    model->setFlyBehavior(new FlyRocketPowered());
    model->performFly();

    delete mallard;
    delete redHead;
    delete rubber;
    delete decoy;
    delete model;
    
}