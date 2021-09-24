#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lifted from http://www.azillionmonkeys.com/qed/hash.html
//
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

uint32_t super_fast_hash(const char *data, int len) {
  uint32_t hash = len, tmp;
  int rem;

  if (len <= 0 || data == NULL)
    return 0;

  rem = len & 3;
  len >>= 2;

  /* Main loop */
  for (; len > 0; len--) {
    hash += get16bits(data);
    tmp = (get16bits(data + 2) << 11) ^ hash;
    hash = (hash << 16) ^ tmp;
    data += 2 * sizeof(uint16_t);
    hash += hash >> 11;
  }

  /* Handle end cases */
  switch (rem) {
  case 3:
    hash += get16bits(data);
    hash ^= hash << 16;
    hash ^= ((signed char)data[sizeof(uint16_t)]) << 18;
    hash += hash >> 11;
    break;
  case 2:
    hash += get16bits(data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1:
    hash += (signed char)*data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }

  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;

  return hash;
}
// end lift

typedef struct hash_table_rec {
  struct hash_table_rec *next; // use in open addressing
  const char *key;
  unsigned int value; // TODO: is this okay?
} hash_table_rec_t;

#define TABLE_SIZE 1000

typedef struct some_value {
  int a;
  unsigned int b;
  char *c;
} some_val_t;

int main() {
  printf("%i\t%i\t%i\t\n", super_fast_hash("hey", 2) % 10,
         super_fast_hash("hey", 2) % 10,
         super_fast_hash("SUPEWRAFWECEWFWEFIJEFIEIJFIEJFIJEIFJIEJFIJEF", 44) %
             10);

  hash_table_rec_t *table = calloc(TABLE_SIZE, sizeof(hash_table_rec_t));
  uint32_t hash_result = super_fast_hash("hi", 2) % TABLE_SIZE;

  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] =
        (hash_table_rec_t){.key = NULL}; // TODO: lets think about null items
    // table[i] = NULL_ITEM;
  }

  some_val_t *val = malloc(sizeof(some_val_t));
  val = &(some_val_t){1, 2, "bla"};
  const char *key = "hey";
  if (table[hash_result].key != NULL) {
    if (strcmp(table[hash_result].key, key) != 0) { // if key not equal
      puts("found");
    } else {
      puts("hash collision"); // TODO: open addressing
    }
  }

  hash_table_rec_t item = {
      .next = NULL, .key = key, .value = (unsigned int)val};
  table[hash_result] = item;
}
