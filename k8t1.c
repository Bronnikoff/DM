#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;

int gamiltonc (int k, int vo, int a[n][n]);
void prnt(int q);
int gamiltonp (int k, int vo, int a[n][n]);
int eiler(int a[n][n], int w, int vo);
int eilerc(int a[n][n], int w, int vo);
void prntei(int q);


int *path, *st;
int *c;

int gamiltonc(int k, int vo, int a[n][n])
{
  int v, q1=0;
  for(v=0; v<n; v++)
    {
      if (a[path[k-1]][v])
	{
	  if(k==n && v==vo)
	    {
	      q1=1;
	      prnt(1);
	    }
	  else if (c[v]==-1)
	    {
	      c[v]=k;
	      path[k]=v;
	      if (q1!=1)
		{
		  q1=gamiltonc(k+1, vo, a);
		}
	      else
		{
		  gamiltonc(k+1, vo, a);
		}
		  c[v]=-1;
	    }
	}}
  return q1;
}

int gamiltonp(int k, int vo, int a[n][n])
{
  int v, q1=0;
  for(v=0; v<n; v++)
    {
      if (a[path[k-1]][v]==1)
	{
	  if((k==(n-1))&&(c[v]==-1))
	    {
	      c[v]=k;
	      path[k]=v;
	      q1=1;
	      prnt(0);
	      c[v]=-1;
	    }
	  else if (c[v]==-1)
	    {
	      c[v]=k;
	      path[k]=v;
	      if (q1!=1)
		{
		  q1=gamiltonp(k+1, vo, a);
		}
	      else
		{
		  gamiltonp(k+1, vo, a);
		}
		  c[v]=-1;
	    }
	}}
  return q1;
}

int eiler(int a[n][n], int w, int vo)
{
  int b[n][n], i, j, z=0;
   w+=1;
  st=(int*)realloc(st, w*sizeof(int));
  st[w-1]=vo;
  for (i=0; i<n; i++)
    {
      for (j=0; j<n; j++)
	{
	  b[i][j]=a[i][j];
	  if (b[i][j]==1)
	    {
	      z=1;
	    }
	}
    }
  if(z==0)
    {
      prntei(w);
      return 1;
    }
 
  z=0;
  for (j=0; j<n; j++)
    {
      if(a[vo][j]!=0)
	{
	  if(a[j][vo]!=0)
	    {
	      i=1;
	    }
	  else
	    {
	      i=0;
	    }
	  b[vo][j]=0;
	  b[j][vo]=0;
	  z=z+eiler(b, w, j);
	  b[vo][j]=1;
	  if(i==1)
	    {
	  b[j][vo]=1;
	    }
	}
    }
      return z;
}

int eilerc(int a[n][n], int w, int vo)
{
  int b[n][n], i, j, z=0;
   w+=1;
  st=(int*)realloc(st, w*sizeof(int));
  st[w-1]=vo;
  for (i=0; i<n; i++)
    {
      for (j=0; j<n; j++)
	{
	  b[i][j]=a[i][j];
	  if (b[i][j]==1)
	    {
	      z=1;
	    }
	}
    }
  if(z==0)
    {
      if(vo==st[0])
	{
      prntei(w);
      return 1;
	}
      else
	{
	  return 0;
	}
    }
 
  z=0;
  for (j=0; j<n; j++)
    {
      if(a[vo][j]!=0)
	{
	  if(a[j][vo]!=0)
	    {
	      i=1;
	    }
	  else
	    {
	      i=0;
	    }
	  b[vo][j]=0;
	  b[j][vo]=0;
	  z=z+eilerc(b, w, j);
	  b[vo][j]=1;
	  if(i==1)
	    {
	  b[j][vo]=1;
	    }
	}
    }
      return z;
}

  void prntei(int q)
{
  int p;
  printf("%d ", st[0]+1);
  for (p=1; p<q; p++)
    {
    printf("-> %d ", st[p]+1);
    }
      printf("\n");    
}

void prnt(int q)
{
  int p;
  printf("%d ", path[0]+1);
  for (p=1; p<n; p++)
    {
    printf("-> %d ", path[p]+1);
    }
  if (q==1)
    {
  printf("-> %d\n", path[0]+1);
    }
  else
    {
      printf("\n");
    }
}

int main(int argc, char* argv[])
{
  int i, j, vo;
  FILE *f, *k;
  if (argc != 4)
    {
      printf ("ERROR!\n");
      return 1;
    }
  k=fopen(argv[2], "wb");
  f=fopen(argv[1], "r");
  fscanf(f, "%d", &n);
    int a[n][n];
  for (i=0; i<n; i++)
    {
      for (j=0; j<n; j++)
	{
	  fscanf(f, "%d", &a[i][j] );
	}
    }
  fclose(f);
  c=(int*)malloc(n*sizeof(int));
  path=(int*)malloc(n*sizeof(int));  
  i=atoi(argv[3]);
      switch(i)
	{
	case 0:
	  {
	    fprintf(k, "digraph E { \n");
	    for (i=0; i<n-1; i++)
	      {
	        for (j=i+1; j<n; j++)
		  {
		    if (a[i][j]!=0)
		      {
			    fprintf(k, "v%d -> v%d", i+1, j+1);
			    if (a[j][i]!=0)
			      {
				fprintf(k, " [dir=none];\n");
			      }
			    else
			      {
				fprintf(k, ";\n");
			      }
		      }
		    else if (a[j][i]!=0)
		      {
			fprintf(k, "v%d -> v%d;\n", j+1, i+1);
		      }
		  }
	      }
	    fprintf(k, "} \n");
	    printf("\n");
	    break;
	  }
	  
	case 1:
	  {
  printf("\nГамильтоновы циклы:\n");
      printf("Введите номер вершины, от которой следует искать циклы(0 для поиска всех циклов графа)!\nВаш выбор:");
      scanf("%d", &i);
        printf("\n");
      if (i==0)
	{
  for (vo=0; vo<n; vo++)
  {
  for(j=0; j<n; j++)
    {
      c[j]=-1;
    }
  path[0]=vo;
  c[vo]=vo;
  printf("От v%d:\n", vo+1);
  if(gamiltonc (1, vo, a))
    {
      printf("\n");
    }
  else
    {
      printf("Нет путей\n");
    }
}
	}
      else if (i<=n)
	{
	  vo=i-1;
	  for(j=0; j<n; j++)
    {
      c[j]=-1;
    }
  path[0]=vo;
  c[vo]=vo;
  printf("От v%d:\n", vo+1);
  if(gamiltonc (1, vo, a))
    {
      printf("\n");
    }
   else
    {
      printf("Нет путей\n");
    }
	}
      else
	{
	  printf("Ошибка! Нет вершины с таким номером!\n");
	}
      printf("\n");
  break;
	  }

	case 2:
	  {
    printf("\nГамильтоновы пути:\n");
      printf("Введите номер вершины, от которой следует искать пути(0 для поиска всех путей графа)!\nВаш выбор:");
      scanf("%d", &i);
        printf("\n");
      if (i==0)
	{
  for (vo=0; vo<n; vo++)
  {
  for(j=0; j<n; j++)
    {
      c[j]=-1;
    }
  path[0]=vo;
  c[vo]=vo;
  printf("От v%d:\n", vo+1);
  if(gamiltonp (1, vo, a))
    {
      printf("\n");
    }
  else
    {
      printf("Нет путей\n");
    }
}
	}
      else if (i<=n)
	{
	  vo=i-1;
	  for(j=0; j<n; j++)
    {
      c[j]=-1;
    }
  path[0]=vo;
  c[vo]=vo;
  printf("От v%d:\n", vo+1);
  if(gamiltonp (1, vo, a))
    {
      printf("\n");
    }
   else
    {
      printf("Нет путей\n");
    }
	}
      else
	{
	  printf("Ошибка! Нет вершины с таким номером!\n");
	  }
  break;
	  }

	case 3:
	  {
  printf("\nЭйлеровы пути:\n");
   printf("Введите номер вершины, от которой следует искать пути(0 для поиска всех путей графа)!\nВаш выбор:");
      scanf("%d", &i);
        printf("\n");
      if(i==0)
	{
	  for(j=0; j<n; j++)
	    {
	      vo=j;
	      printf("От v%d:\n", vo+1);
  if (eiler(a, 0, vo)==0)
    {
      printf("Нет путей\n\n");
    }
	    }
	}
      else if(i<=n)
	{
	  vo=i-1;
	  printf("От v%d:\n", i);
  if (eiler(a, 0, vo)==0)
    {
      printf("Нет путей\n\n");
    }
	}
      else
	{
	  printf("Ошибка! Нет вершины с таким номером!\n");
	}  
  break;
	  }

	case 4:
	  {
   printf("\nЭйлеровы циклы:\n");
   printf("Введите номер вершины, от которой следует искать циклы(0 для поиска всех циклов графа)!\nВаш выбор:");
      scanf("%d", &i);
        printf("\n");
      if(i==0)
	{
	  for(j=0; j<n; j++)
	    {
	      vo=j;
	      printf("От v%d:\n", vo+1);
  if (eilerc(a, 0, vo)==0)
    {
      printf("Нет путей\n\n");
    }
	    }
	}
      else if(i<=n)
	{
	  vo=i-1;
	  printf("От v%d:\n", i);
  if (eilerc(a, 0, vo)==0)
    {
      printf("Нет путей\n\n");
    }
	}
      else
	{
	  printf("Ошибка! Нет вершины с таким номером!\n");
	}
 
  break;
	  }
	case 5:
	  {
	    printf("Выполнил Бронников М.А.(М8О-104Б-17)\nВыход!\n");
	    return 0;
	    break;
	  }
	default:
	  {
	    printf("Ошибка! Нет такого варианта!\n");
	    return 1;
	  }
	}
  return 0;
}
  


