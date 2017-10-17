
package kmaptemp;

//import javax.script.ScriptEngine;
//import javax.script.ScriptEngineManager;
//import javax.script.ScriptException;

/**
 *
 * @author danish
 */
public
	class Kmaptemp
{

    /**
     * @param args the command line arguments
     */
    public static
	    void main(String[] args)
    {
	// TODO code application logic here
		
		int n=4;
		int[][] array={{0,0,0,1},
                       {0,1,1,1},
                       {0,0,1,0},
                       {0,0,0,1},};
				
		System.out.print("\n\n");
		
        for (int[] array1 : array)
        {
            for (int j = 0; j < array1.length; j++)
            {
                if (array1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (array1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
/*
        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("js");
        Object result = engine.eval("4+5");

        System.out.print("\n");
        System.out.print(result.toString());
        System.out.print("\n\n");
*/
        int[][] ones = new int[n][n];
        int[][] rowTwos = new int[n][n];
        int[][] rowFours = new int[n][n];
		int[][] rowDupl = new int[n][n];
        int[][] colTwos = new int[n][n];
        int[][] colFours = new int[n][n];
		int[][] colDupl = new int[n][n];
		int[][] square = new int[n][n];
		int[][] flag = new int[n][n];
        
        // DOING THE STUFF -----------------
        
		for (int i = 0; i < (array.length); i++) // COPY ARRAY TO ONES
        {
			System.arraycopy(array[i], 0, ones[i], 0, array[i].length);
        }
		
        for (int i = 0; i < array.length; i++)
        {
			int rowDone=0;
            for (int j = 0; j < (array[i].length); j++)
            {
				if (j==n-1) // FLLING ROWTWOS
				{
					if (array[i][j]==1&&array[i][0]==1)
					{
						rowTwos[i][j]=1;
						ones[i][j]=0;
						ones[i][0]=0;
						flag[i][j]=-1;
						flag[i][0]=-1;
					}
				}
                else // FLLING ROWTWOS
				{
					if (array[i][j]==1&&array[i][j+1]==1)
					{
						rowTwos[i][j]=1;
						ones[i][j]=0;
						ones[i][j+1]=0;
						flag[i][j]=-1;
						flag[i][j+1]=-1;
					}
				}
				
                if (rowDone==0) // FILLING ROWFOURS
				{
					if(array[i][j]==0)
					{
						rowFours[i][0]=0;
						rowDone=1;
					}
					else
					{
						rowFours[i][0]=1;
					}
				}
            }
			
			if (rowFours[i][0]==1)
			{
				for (int j = 0; j < (array[i].length); j++)
				{	
					flag[i][j]=-1;
				}
			}
        }
        for (int i = 0; i < (array.length); i++)
        {
			int colDone=0;
            for (int j = 0; j < (array[i].length); j++)
            {
				if(i==n-1) // FILLING COLTWOS
				{
					if (array[i][j]==1&&array[0][j]==1&&(flag[i][j]!=-1||flag[0][j]!=-1))
					{
						colTwos[i][j]=1;
						ones[i][j]=0;
						ones[0][j]=0;
					}
				}
				else // FILLING COLTWOS
				{
					if (array[i][j]==1&&array[i+1][j]==1&&(flag[i][j]!=-1||flag[i+1][j]!=-1))
					{
						colTwos[i][j]=1;
						ones[i][j]=0;
						ones[i+1][j]=0;
					}
				}
				
				if (colDone==0) // FILLING COLFOURS
				{
					if(array[j][i]==0)
					{
						colFours[0][i]=0;
						colDone=1;
					}
					else
					{
						colFours[0][i]=1;
					}
				} 
            }
			
			if (colFours[i][0]==1)
			{
				for (int j = 0; j < (array[i].length); j++)
				{	
					flag[j][i]=-1;
				}
			}
        }
		
		for (int i = 0; i < array.length; i++) // FILLING SQUARES
        {
            for (int j = 0; j < (array[i].length); j++)
            {
				if (j==(n-1)&&i!=(n-1))
				{
					if (array[i][j]==1&&array[i][0]==1&&array[i+1][j]==1&&array[i+1][0]==1)
					{
						square[i][j]=1;
					}
				}
				else if (i==(n-1)&&j!=(n-1))
				{
					if (array[i][j]==1&&array[i][j+1]==1&&array[0][j]==1&&array[0][j+1]==1)
					{
						square[i][j]=1;
					}
				}
				else if (i==n-1&&j==n-1)
				{
					if (array[i][j]==1&&array[0][0]==1&&array[i][0]==1&&array[0][j]==1)
					{
						square[i][j]=1;
					}
				}
                else
				{
					if (array[i][j]==1&&array[i][j+1]==1&&array[i+1][j]==1&&array[i+1][j+1]==1)
					{
						square[i][j]=1;
					}
				}
            }
        }
		
		for (int i = 0; i < (array.length); i++)
        {
			if(rowFours[i][0]==1)
			{
				for (int j = 0; j < (array[i].length); j++) // REMOVING ROWTWOS USING ROWFOURS
				{
					rowTwos[i][j]=0;
					ones[i][j]=0;
				}
			}
			if(colFours[0][i]==1)
			{
				for (int j = 0; j < (array[i].length); j++) // REMOVING COLTWOS USING COLFOURS
				{
					colTwos[j][i]=0;
					ones[j][i]=0;
				}
			}
		}
		
		for (int i = 0; i < (array.length); i++) // REMOVING USING SQUARE
        {
			for (int j = 0; j < (array[i].length); j++)
			{
				if (j==(n-1)&&i!=(n-1))
				{
					if (square[i][j]==1)
					{
						ones[i][j]=0;
						ones[i][0]=0;
						ones[i+1][j]=0;
						ones[i+1][0]=0;
						rowTwos[i][j]=0;
						rowTwos[i+1][j]=0;
						colTwos[i][j]=0;
						colTwos[i][0]=0;
					}
				}
				else if (i==(n-1)&&j!=(n-1))
				{
					if (square[i][j]==1)
					{
						ones[i][j]=0;
						ones[i][j+1]=0;
						ones[0][j]=0;
						ones[0][j+1]=0;
						rowTwos[i][j]=0;
						rowTwos[0][j]=0;
						colTwos[i][j]=0;
						colTwos[i][j+1]=0;
					}
				}
				else if (i==n-1&&j==n-1)
				{
					if (square[i][j]==1)
					{
						ones[i][j]=0;
						ones[0][0]=0;
						ones[i][0]=0;
						ones[0][j]=0;
						rowTwos[i][j]=0;
						rowTwos[0][j]=0;
						colTwos[i][j]=0;
						colTwos[i][0]=0;
					}
				}
                else
				{
					if (square[i][j]==1)
					{
						ones[i][j]=0;
						ones[i][j+1]=0;
						ones[i+1][j]=0;
						ones[i+1][j+1]=0;
						rowTwos[i][j]=0;
						rowTwos[i+1][j]=0;
						colTwos[i][j]=0;
						colTwos[i][j+1]=0;
					}
				}
			}
		}
		
		for (int i = (rowFours.length)-1; i >= 0; i--) // REMOVING ROWFOURS USING ROWDUPL
        {
			if (i==n-1)
			{
				if (rowFours[i][0]==1&&rowFours[0][0]==1)
				{
					rowDupl[i][0]=1;
					rowFours[i][0]=0;
					if (rowFours[1][0]==0)
					{
						rowFours[0][0]=0;
					}
					for (int j = 0; j < (array[i].length); j++) // REMOVING SQUARES USING ROWDUPL
					{
						square[i][j]=0;
					}
				}
			}
			else
			{
				if (rowFours[i][0]==1&&rowFours[i+1][0]==1)
				{
					rowDupl[i][0]=1;
					rowFours[i][0]=0;
					rowFours[i+1][0]=0;
					for (int j = 0; j < (array[i].length); j++) // REMOVING SQUARES USING ROWDUPL
					{
						square[i][j]=0;
					}
				}
			}
        }
		
		for (int j = (colFours.length)-1; j >= 0; j--) // REMOVING COLFOURS USING COLDUPL
        {
			if (j==n-1)
			{
				if (colFours[0][j]==1&&colFours[0][0]==1)
				{
					colDupl[0][j]=1;
					colFours[0][j]=0;
					if (colFours[0][1]==0)
					{
						colFours[0][0]=0;
					}
					for (int i = 0; i < (array[j].length); i++) // REMOVING SQUARES USING COLDUPL
					{
						square[i][j]=0;
					}
				}
			}
			else
			{
				if (colFours[0][j]==1&&colFours[0][j+1]==1)
				{
					colDupl[0][j]=1;
					colFours[0][j]=0;
					colFours[0][j+1]=0;
					for (int i = 0; i < (array[j].length); i++) // REMOVING SQUARES USING COLDUPL
					{
						square[i][j]=0;
					}
				}
			}
        }
		
		for (int i = 0; i < (array.length); i++) // REMOVING COLTWOS USING ROWDUPL
        {
			if (rowDupl[i][0]==1)
			{
				for (int j = 0; j < (array[i].length); j++)
				{
					colTwos[i][j]=0;
				}
			}
		}
		for (int i = 0; i < (array.length); i++) // REMOVING ROWTWOS USING COLDUPL
        {
			if (colDupl[0][i]==1)
			{
				for (int j = 0; j < (array[i].length); j++)
				{
					rowTwos[j][i]=0;
				}
			}
		}
		
        // PRITNING THE STUFF ---------------------
        
		System.out.print("\nONES:\n");
		
		for (int[] ones1 : ones)
        {
            for (int j = 0; j < ones.length; j++)
            {
                if (ones1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (ones1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nROWTWOS:\n");
		
        for (int[] rowTwos1 : rowTwos)
        {
            for (int j = 0; j < rowTwos1.length; j++)
            {
                if (rowTwos1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (rowTwos1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
        
        System.out.print("\nCOLTWOS:\n");
        
        for (int[] colTwos1 : colTwos)
        {
            for (int j = 0; j < colTwos1.length; j++)
            {
                if (colTwos1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (colTwos1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nSQUARE:\n");
		
		for (int[] square1 : square)
        {
            for (int j = 0; j < square.length; j++)
            {
                if (square1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (square1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nROWFOURS:\n");
		
		for (int[] rowFours1 : rowFours)
        {
            for (int j = 0; j < rowFours1.length; j++)
            {
                if (rowFours1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (rowFours1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nCOLFOURS:\n");
		
		for (int[] colFours1 : colFours)
        {
            for (int j = 0; j < colFours1.length; j++)
            {
                if (colFours1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (colFours1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nROWDUPL:\n");
		
		for (int[] rowDupl1 : rowDupl)
        {
            for (int j = 0; j < rowDupl.length; j++)
            {
                if (rowDupl1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (rowDupl1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nCOLDUPL:\n");
		
		for (int[] colDupl1 : colDupl)
        {
            for (int j = 0; j < colDupl.length; j++)
            {
                if (colDupl1[j] == 1)
                {
                    System.out.print("1 ");
                }
                else if (colDupl1[j] == 0)
                {
                    System.out.print("0 ");
                }
            }
            System.out.print("\n");
        }
		
		System.out.print("\nANSWER:\n"); // ANSWER ------------------
		
		for (int i = 0; i < (array.length); i++)
        {
			for (int j = 0; j < (array[i].length); j++)
			{
				if(ones[i][j]==1)
				{
					switch (j)
					{
						case 0:
							System.out.print("A'B'");
							break;
						case 1:
							System.out.print("A'B");
							break;
						case 2:
							System.out.print("AB");
							break;
						case 3:
							System.out.print("AB'");
							break;
						default:
							break;
					}
					
					switch (i)
					{
						case 0:
							System.out.print("C'D'");
							break;
						case 1:
							System.out.print("C'D");
							break;
						case 2:
							System.out.print("CD");
							break;
						case 3:
							System.out.print("CD'");
							break;
						default:
							break;
					}
					System.out.print(" + ");
				}
			}
		}
		
		for (int i = 0; i < (array.length); i++)
        {
			for (int j = 0; j < (array[i].length); j++)
			{
				if(rowTwos[i][j]==1)
				{
					switch (j)
					{
						case 0:
							System.out.print("A'");
							break;
						case 1:
							System.out.print("B");
							break;
						case 2:
							System.out.print("A");
							break;
						case 3:
							System.out.print("B'");
							break;
						default:
							break;
					}
					
					switch (i)
					{
						case 0:
							System.out.print("C'D'");
							break;
						case 1:
							System.out.print("C'D");
							break;
						case 2:
							System.out.print("CD");
							break;
						case 3:
							System.out.print("CD'");
							break;
						default:
							break;
					}
					System.out.print(" + ");
				}
			}
		}
		
		for (int i = 0; i < (array.length); i++)
        {
			for (int j = 0; j < (array[i].length); j++)
			{
				if(colTwos[j][i]==1)
				{
					switch (j)
					{
						case 0:
							System.out.print("A'B'");
							break;
						case 1:
							System.out.print("A'B");
							break;
						case 2:
							System.out.print("AB");
							break;
						case 3:
							System.out.print("AB'");
							break;
						default:
							break;
					}
					
					switch (i)
					{
						case 0:
							System.out.print("C'");
							break;
						case 1:
							System.out.print("D");
							break;
						case 2:
							System.out.print("D");
							break;
						case 3:
							System.out.print("D'");
							break;
						default:
							break;
					}
					System.out.print(" + ");
				}
			}
		}
		
		for (int i = 0; i < (array.length); i++)
        {
			for (int j = 0; j < (array[i].length); j++)
			{
				if(square[i][j]==1)
				{
					switch (j)
					{
						case 0:
							System.out.print("A'");
							break;
						case 1:
							System.out.print("B");
							break;
						case 2:
							System.out.print("A");
							break;
						case 3:
							System.out.print("B'");
							break;
						default:
							break;
					}
					
					switch (i)
					{
						case 0:
							System.out.print("C'");
							break;
						case 1:
							System.out.print("D");
							break;
						case 2:
							System.out.print("C");
							break;
						case 3:
							System.out.print("D'");
							break;
						default:
							break;
					}
					System.out.print(" + ");
				}
			}
		}
		
		for (int i = 0; i < (array.length); i++)
		{
			if(rowFours[i][0]==1)
			{
				switch (i)
				{
					case 0:
						System.out.print("C'D'");
						break;
					case 1:
						System.out.print("C'D");
						break;
					case 2:
						System.out.print("CD");
						break;
					case 3:
						System.out.print("CD'");
						break;
					default:
						break;
				}
				System.out.print(" + ");
			}
		}
	
		for (int i = 0; i < (array.length); i++)
		{
			if(colFours[0][i]==1)
			{
				switch (i)
				{
					case 0:
						System.out.print("A'B'");
						break;
					case 1:
						System.out.print("A'B");
						break;
					case 2:
						System.out.print("AB");
						break;
					case 3:
						System.out.print("AB'");
						break;
					default:
						break;
				}
				System.out.print(" + ");
			}
		}
	
		for (int i = 0; i < (array.length); i++)
		{
			if(rowDupl[i][0]==1)
			{
				switch (i)
				{
					case 0:
						System.out.print("C'");
						break;
					case 1:
						System.out.print("D");
						break;
					case 2:
						System.out.print("D");
						break;
					case 3:
						System.out.print("D'");
						break;
					default:
						break;
				}
				System.out.print(" + ");
			}
		}
	
		for (int i = 0; i < (array.length); i++)
		{
			if(colDupl[0][i]==1)
			{
				switch (i)
				{
					case 0:
						System.out.print("A'");
						break;
					case 1:
						System.out.print("B");
						break;
					case 2:
						System.out.print("A");
						break;
					case 3:
						System.out.print("B'");
						break;
					default:
						break;
				}
				System.out.print(" + ");
			}
		}
		
		System.out.print("\n\n");
    }
}