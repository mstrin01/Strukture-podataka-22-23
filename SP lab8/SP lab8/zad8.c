#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.
*/

struct _stablo;
typedef struct _stablo* position;
typedef struct _stablo {

	int el;
	position left;
	position right;
}stablo;

int Meni();
position unesiElement(position, int);
position stvoriNovi(int);
int ispisInorder(position);
int ispisPreorder(position);
int ispisPostorder(position);
int dubinaStabla(position);
int ispisTrenutneRazine(position,int);
int ispisLevelorder(position);
position pronadjiEl(position, int);
position izbrisiEl(position, int);
position pronadjiMax(position);
position pronadjiMin(position);


int main()
{
	position root = NULL;
	position temp = NULL;

	int izbor = 0, uvjet = 1;
	int element = 0;

	while (uvjet)
	{
		Meni();
		printf("Izaberite broj: \n");
		scanf("%d", &izbor);
		puts("\n");
		switch (izbor) 
		{
		case 1:
			printf("\nUnesi element koji zelis unijeti: \n\n");
			scanf("%d", &element);
			root = unesiElement(root, element);
			if (root == NULL)
			{
				printf("Taj se element vec nalazi u stablu!\n");
			}

			break;

		case 2:
			ispisInorder(root);
			break;

		case 3:
			ispisPreorder(root);
			break;

		case 4:
			ispisPostorder(root);
			break;

		case 5:
			ispisLevelorder(root);
			break;

		case 6:
			printf("\nUnesi element koji zelis pronaci: \n\n");
			scanf("%d", &element);

			temp = pronadjiEl(root, element);
			if (!temp)
			{
				printf("Element nije pronadjen!\n");
			}
			else
				printf("Element je pronadjen!\n");

			break;
			
		case 7:
			printf("\nUnesi element koji zelis izbrisati: \n\n");
			scanf("%d", &element);

			root = izbrisiEl(root, element);
			break;

		case 8:
			uvjet = 0;
			break;


		default:
			printf("Unesen krivi znak!\n");
			break;
		
		}
	}

	return 0;
}

int Meni()
{
	printf("----------------------\n");
	printf("  1 - Unesi element\n");
	printf("  2 - Ispisi inorder\n");
	printf("  3 - Ispisi preorder\n");
	printf("  4 - Ispisi postorder\n");
	printf("  5 - Ispisi levelorder\n");
	printf("  6 - Pronadi element\n");
	printf("  7 - Izbrisi element\n");
	printf("  8 - Izlaz\n");
	printf("-----------------------\n");

	return 0;
}

position unesiElement(position root, int element)
{
	position noviEl = NULL;

	if (root == NULL)
	{
		noviEl = stvoriNovi(element);
		return noviEl;
	}

	if (element < root->el)
	{
		root->left = unesiElement(root->left, element);
	}

	else if (element > root->right)
	{
		root->right = unesiElement(root->right, element);
	}

	else 
	{
		free(noviEl);
	}

	return root;
}

position stvoriNovi(int element)
{
	position noviEl = NULL;
	noviEl = (position)malloc(sizeof(stablo));
	if (!noviEl)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	noviEl->el = element;
	noviEl->left = NULL;
	noviEl->right = NULL;
	
	return noviEl;

}

int ispisInorder(position root)
{
	if (root != NULL)
	{
		ispisInorder(root->left);
		printf("%d\n", root->el);
		ispisInorder(root->right);

	}
	
	return 0;
}
 
int ispisPreorder(position root)
{
	if (root != NULL)
	{
		printf("%d\n", root->el);
		ispisPreorder(root->left);
		ispisPreorder(root->right);

	}
	
	return 0;
}
int ispisPostorder(position root)
{
	if (root != NULL)
	{
		ispisPostorder(root->left);
		ispisPostorder(root->right);
		printf("%d\n", root->el);

	}
	
	return 0;
}
int dubinaStabla(position root)
{
	int lijevaDubina = 0, desnaDubina = 0;
	if (root == NULL)
	{
		return 0;
	}

	else 
	{
		lijevaDubina = dubinaStabla(root->left);
		desnaDubina = dubinaStabla(root->right);

		if (lijevaDubina > desnaDubina)
			return (lijevaDubina + 1);
		else
			return (desnaDubina + 1);
	}

}
int ispisTrenutneRazine(position root, int razina)
{
	if (root == NULL)
	{
		return;
	}

	if (razina == 1)
	{
		printf("%d\n", root->el);
		return 0;
	}
	else if (razina > 1)
	{
		ispisTrenutneRazine(root->left, razina - 1);
		ispisTrenutneRazine(root->right, razina - 1);
	}
}

int ispisLevelorder(position root)
{
	int dubina = 0, i = 0;
	dubina = dubinaStabla(root);

	for (i = 1; i < dubina; i++)
	{
		ispisTrenutneRazine(root, i);
	}
}
position pronadjiEl(position root, int element)
{
	if (root == NULL)
	{
		return NULL;
	}

	else if (element < root->el)
		return pronadjiEl(root->left, element);

	else if (element > root->el)
		return pronadjiEl(root->right, element);

	else
		return root;
}

position izbrisiEl(position root, int element)
{
	position temp = NULL;

	if (root == NULL)
		return NULL;
	
	if (root->el < element)
	{
		root->right = izbrisiEl(root->right, element);
	}
	
	else if (root->el > element)
	{
		root->left = izbrisiEl(root->left, element);
	}

	else 
	{
		if (root->left)
		{
			temp = pronadjiMax(root->left);
			root->el = temp->el;
			root->left = izbrisiEl(root->left, temp->el);
		}
		else if (root->right)
		{
			temp = pronadjiMin(root->right);
			root->el = temp->el;
			root->right = izbrisiEl(root->right, temp->el);
		}
		else
		{
			free(root);
			return NULL;
		}
	}
	
	return root;
}
position pronadjiMin(position root)
{
	position temp = NULL;
	temp = root;

	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	
	return temp;
}
position pronadjiMax(position root)
{
	position temp = NULL;
	temp = root;

	while (temp->right != NULL)
	{
		temp = temp->right;
	}

	return temp;
}