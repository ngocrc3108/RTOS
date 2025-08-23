#include "mem.h"
#include "system.h"
#include "stdint.h"

/* allocated_memory_link_list_t size must be word aligned */
typedef struct allocated_memory_link_list_t {
    struct allocated_memory_link_list_t* next;
    uint32_t size; // includes link list instance size and aligned alocated memory size
} allocated_memory_link_list_t;

static allocated_memory_link_list_t* list_root = 0;
static uint32_t heap_address = (uint32_t)&__heap_start_address;

static inline allocated_memory_link_list_t* find_next_available_address(allocated_memory_link_list_t* from);

static void link_list_insert_head(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element);
static void link_list_insert(allocated_memory_link_list_t* location, allocated_memory_link_list_t* element);
static void link_list_insert_tail(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element);
static void link_list_remove(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element);

void* malloc(uint32_t size)
{
    /* allocated_memory_link_list_t size must be word aligned */
    const uint32_t aligned_size = sizeof(allocated_memory_link_list_t) + align_memory_size(size);

    if(list_root == 0)
    {
        link_list_insert_head(&list_root, (allocated_memory_link_list_t*)heap_address);

        /* After allocating memory for this link list, the next (size) bytes are for our actual allocated memory */
        heap_address += aligned_size;
        list_root->size = aligned_size;

        return (void*)(list_root+1);
    }

    /* If there is enough space between the start of heap and the root of link list, allocate new memory there and make it the root */
    const uint32_t heap_start_and_root_gap = (uint32_t)list_root - (uint32_t)&__heap_start_address;
    if(heap_start_and_root_gap >= aligned_size)
    {
        const uint32_t allocated_address = (uint32_t)&__heap_start_address + (heap_start_and_root_gap - aligned_size);
        link_list_insert_head(&list_root, (allocated_memory_link_list_t*)allocated_address);
        list_root->size = aligned_size;
        return (void*)(list_root+1);
    }

    /* Normal scenarios */
    allocated_memory_link_list_t* iterator = list_root;
    while(iterator->next != 0)
    {
        if((uint32_t)(iterator->next+1) - ((uint32_t)(iterator+1) + iterator->size) > aligned_size)
        {
            break;
        }

        iterator = iterator->next;
    }

    /* reaches the end of link list */
    if(iterator->next == 0)
    {
        heap_address += aligned_size;
    }

    allocated_memory_link_list_t* new_element = find_next_available_address(iterator);
    new_element->size = aligned_size;
    link_list_insert(iterator, new_element);

    return (void*)(new_element+1);
}

void* calloc(uint32_t nmemb, uint32_t size)
{
    void* allocated_mem = malloc(nmemb * size);
    for(uint32_t i = 0; i < size; i++)
    {
        ((uint8_t*)allocated_mem)[i] = 0;
    }

    return allocated_mem;
}

void free(void* address)
{
    allocated_memory_link_list_t* iterator = list_root;
    while((void*)(iterator+1) != address && iterator->next !=0)
    {
        iterator = iterator->next;
    }

    if((void*)(iterator+1) != address)
    {
        /* should return error */
        return;
    }

    link_list_remove(&list_root, iterator);
}

void link_list_insert_head(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element)
{
    if((*root) == 0)
    {
        (*root) = element;
        (*root)->next = 0;
        return;
    }

    element->next = (*root);
    (*root) = element;
}

void link_list_insert(allocated_memory_link_list_t* location, allocated_memory_link_list_t* element)
{
    element->next = location->next;
    location->next = element;
}

void link_list_insert_tail(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element)
{
    allocated_memory_link_list_t* current_element = (*root);

    while(current_element->next != 0) {current_element = current_element->next;}

    link_list_insert(current_element, element);
}


void link_list_remove(allocated_memory_link_list_t** root, allocated_memory_link_list_t* element)
{
    /* If the target element is the root */
    if(element == *root)
    {
        *root = (*root)->next;
    }

    /* Find the element before the targeted element */
    allocated_memory_link_list_t* current_element = *root;
    while(current_element->next != 0 && current_element->next != element)
    {
        current_element = current_element->next;
    }
    /* element not found */
    if(current_element->next != element)
    {
        return;
    }

    current_element->next = element->next;
    element->next = 0; // NULL
}

allocated_memory_link_list_t* find_next_available_address(allocated_memory_link_list_t* from)
{
    return (allocated_memory_link_list_t*)((uint32_t)(from+1) + from->size);
}
