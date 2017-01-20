public interface BasicList 
{
   void add(int index, java.lang.Object element);
   void add(java.lang.Object element);
   void clear();
   boolean contains(java.lang.Object element);
   java.lang.Object get(int index);
   int indexOf(java.lang.Object element);
   java.lang.Object remove(int index);
   java.lang.Object set(int index,java.lang.Object element);
   int size();
   
}