# include "../inc/set.h"

int main() {

   SET * sp = create_set();

   ITEM * item1 = create_item(1);
   ITEM * item2 = create_item(2);
   ITEM * item3 = create_item(3);
   ITEM * item4 = create_item(4);
   ITEM * item5 = create_item(5);
   ITEM * item6 = create_item(6);
   ITEM * item7 = create_item(7);
   ITEM * item8 = create_item(8);
   ITEM * item9 = create_item(9);
   ITEM * item10 = create_item(10);
   
   

   addElement_set(sp, item1);
   addElement_set(sp, item2);
   addElement_set(sp, item3);
   addElement_set(sp, item4);
   addElement_set(sp, item5);
   addElement_set(sp, item6);
   addElement_set(sp, item7);
   addElement_set(sp, item8);
   addElement_set(sp, item9);
   addElement_set(sp, item10);

   print_set(sp);
   
   return 0;
}
