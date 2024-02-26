class C
{
  public:
    C() {}
    C(double a) {}
    C(const C *o) {}
    C(const C &a, const C &b) {}
    int
    operator~() const
    {
        return 0;
    }
    const C &
    operator++() const
    {
        return *this;
    }
    int
    operator*(const C *o) const
    {
        return 0;
    }
};

const C &
operator+(int a, const C &a2)
{
    return a2;
}
