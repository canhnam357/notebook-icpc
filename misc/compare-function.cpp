class Compare
{
public:
    bool operator() (const string &a, const string &b) const
    {
        return a + b > b + a;
    }
};