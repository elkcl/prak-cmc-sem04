class Figure
{
public:
    virtual ~Figure() {}
    virtual bool equals(const Figure *f) const = 0;
};

class Rectangle : public Figure
{
private:
    int a, b;

public:
    Rectangle(int a_, int b_)
    {
        a = a_;
        b = b_;
    }
    virtual bool
    equals(const Figure *f) const
    {
        const Rectangle *o = dynamic_cast<const Rectangle *>(f);
        return o && a == o->a && b == o->b;
    }
};

class Triangle : public Figure
{
private:
    int a, b, c;

public:
    Triangle(int a_, int b_, int c_)
    {
        a = a_;
        b = b_;
        c = c_;
    }
    virtual bool
    equals(const Figure *f) const
    {
        const Triangle *o = dynamic_cast<const Triangle *>(f);
        return o && a == o->a && b == o->b && c == o->c;
    }
};
