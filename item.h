#ifndef ITEM_H
#define ITEM_H

//One item, 3 chars info pointers so actuall text lives inside malloced memory
struct _Item
{
  double price;
  char *sku;
  char *name;
  char *category;
};
typedef struct _Item Item;   // now "Item" is "struct _Item"

#endif
