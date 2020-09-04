bool isPower2(int x) 
{ 
     return x && (!(x & (x - 1)));
}
