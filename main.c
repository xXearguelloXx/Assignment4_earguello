#include <stdio.h>    //need ts
#include <stdlib.h>   //malloc stuffs
#include <string.h>   //string functions
#include "item.h"     //struct Item

#define NUM_ITEMS 5

//Prototypes for all functions
void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index);
void free_items(Item *item_list, int size);
double average_price(Item *item_list, int size);
void print_items(Item *item_list, int size);


//Add item function
void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index)
{
  //Grab pointer to spot were filling &item_list[index] = item_list + index = base + index*32bytes
  Item *it = &item_list[index];

  //Price is a double, so just copy the value
  it->price = price;

  //For each string gotta allocate strlen+1 (room for '\0'), then copy
  it->sku = malloc(strlen(sku) + 1);
  strcpy(it->sku, sku);

  it->name = malloc(strlen(name) + 1);
  strcpy(it->name, name);

  it->category = malloc(strlen(category) + 1);
  strcpy(it->category, category);
}


//Print item function
void print_items(Item *item_list, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("###############\n");
    printf("item name = %s\n", item_list[i].name);
    printf("item sku = %s\n", item_list[i].sku);
    printf("item category = %s\n", item_list[i].category);
    printf("item price = %f\n", item_list[i].price);   /* %f → 6 decimals, like the example */
  }
  printf("###############\n");
}


//Average price function
double average_price(Item *item_list, int size)
{
  double sum = 0.0;
  for (int i = 0; i < size; i++)
  {
    sum += item_list[i].price;
  }
  return sum / size;
}


//Free item function
void free_items(Item *item_list, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(item_list[i].sku);
    free(item_list[i].name);
    free(item_list[i].category);
  }
  free(item_list);   //outer last
}


//Now, our main function
int main(int argc, char *argv[])
{
  //Check the input
  if (argc < 2)
  {
    printf("Invalid input, type SKU, ex. ./main 67676\n");
    return 1;
  }

  //Space for 5 Items (5 * 32 = 160 bytes), contents still garbage
  Item *item_list = malloc(NUM_ITEMS * sizeof(Item));
  if (item_list == NULL)
  {
    printf("malloc failed\n");
    return 1;
  }

  //Now fill every slot. Order is: price, sku, CATEGORY, NAME, index
  add_item(item_list, 5.00,  "19282", "breakfast", "reese's cereal", 0);
  add_item(item_list, 3.95,  "79862", "dairy",     "milk",           1);
  add_item(item_list, 2.49,  "42069", "produce",   "bananas",        2);
  add_item(item_list, 12.99, "67676", "meat",      "ribeye steak",   3);
  add_item(item_list, 6.75,  "50001", "bakery",    "sourdough loaf", 4);

  //Print functions
  print_items(item_list, NUM_ITEMS);
  printf("average price of items = %f\n", average_price(item_list, NUM_ITEMS));

  //Search by SKU from the command line
  char *search_sku = argv[1];
  int ct = 0;

  //Bounds check FIRST, so short-circuit protects item_list[ct]
  while (ct < NUM_ITEMS && strcmp(item_list[ct].sku, search_sku) != 0)
  {
    ct++;
  }

  //if ct == NUM_ITEMS then loop ran off the end, not found
  //if ct <  NUM_ITEMS then strcmp returned 0 at index ct
  if (ct < NUM_ITEMS)
  {
    printf("\n\nitem found:\n\n");
    print_items(&item_list[ct], 1); //Reuse print_items on a "list" of 1
  }
  else
  {
    printf("item not found\n");
  }

  //Free everything with our function
  free_items(item_list, NUM_ITEMS);
  return 0;
}
