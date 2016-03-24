template <typename T>
class Option
{
  private:
    T* val;
    bool exist;
  public:
    Option(T& v): exist(true), val(&v) {}
    Option(): exist(false), val(0) {}
    Option(Option& o) : exist(o.exist), val(o.val) {}
    
    T& getVal() { return *val; }
    const T& getVal() const { return *val; }
    bool exists() const { return exist; }
    Option<T>& operator= (Option<T>& op) { exist = op.exist; val = op.val; }
    Option<T>& operator= (T& v) { val = &v; exist = true; }
    void disable() { val = 0; exist = true; }
    
};

