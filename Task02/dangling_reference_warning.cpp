// Deliberately unsafe example for compiler-diagnostic evidence only.
// Never call brokenReference() or use its return value: the local has died.
int& brokenReference()
{
    int local = 42;
    return local; // expected -Wreturn-local-addr diagnostic on GCC
}

int main()
{
    return 0;
}
