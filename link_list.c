#include "shell.h"

/**
 * first_node - new node at the beggining
 * @head:fist node
 * @str: input
 * index: index num
 * Return: list
 */
list_t *first_node(list_t **head, char *str, int index)
{
	list_t *new_node;

	if (head == NULL)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (str)
	{
		new_node->str = strdup(str);
		if (new_node->str == NULL)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}
/**
 * last_node - adds new node at the end
 * @head: first node
 * @str: input
 * @index: location node
 * Return: list
 */
list_t *last_node(list_t **head, char *str, int index)
{
	list_t *new_node, *node;

	if (head == NULL)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (str)
	{
		new_node->str = strdup(str);
		if (new_node->str == NULL)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node != NULL)
	{
		while ((*node).next)
			node = (*node).next;
		(*node).next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}
/**
 * delete_node -removes node
 * @head: first node
 * @num: index
 * Return: 1 for success 0 otherwise
 */
int delete_node(list_t **head, int num)
{
	list_t *new_node, *prev_node;
	int i = 0;

	if (!num)
	{
		new_node = *head;
		*head = (*head)->next;
		free(new_node->str);
		free(new_node);
		return (1);
	}
	new_node = *head;
	while (new_node)
	{
		if (i == num)
		{
			prev_node->next = new_node->next;
			free(new_node);
			return (1);
		}
		i++;
		prev_node = new_node;
		new_node = new_node->next;
	}
	return (0);
}
