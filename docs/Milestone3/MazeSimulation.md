``` python
import math
import queue
from graphics import *
from time import sleep
import random

class MazeNode:
	def __init__(self, x, y, maze):
		self.x = x
		self.y = y

		self.up = True
		self.down = True
		self.left = True
		self.right = True

		self.visited = False
		self.isCurr = False

		self.maze = maze

	def visit(self):
		self.maze.currNode.isCurr=False
		self.maze.currNode = self
		self.visited = True
		self.isCurr = True

		self.maze.visitedNodes += 1
		print(self.maze.visitedNodes)
		if(self.maze.visitedNodes == self.maze.cols*self.maze.rows):
			print("DONE!!!!")
			self.maze.notDone = False

	def reset(self):
		self.visited = False

	def toString(self):
		if(self.isCurr):
			return "R"
		elif(self.visited):
			return "x"
		else:
			return "o"

class Maze:
	def __init__(self, cols, rows):
		
		# maze[i][j] is the node at row i and column j
		self.cols = cols
		self.rows = rows

		self.visitedNodes = 0
		self.maze = [[MazeNode(i,j, self) for j in range(cols)] for i in range(rows)]

		self.currNode = self.maze[0][0]
		self.currNode.isCurr = True

		# size of the grid in the graphics
		self.gridSize = 50
		self.win=GraphWin("Maze", self.gridSize*self.cols, self.gridSize*self.rows)

		#handle edges so robot doesnt go off the map
		for i in range(rows):
			self.maze[i][0].left = False
			self.maze[i][cols-1].right = False
		for i in range(cols):
			self.maze[0][i].up = False
			self.maze[rows-1][i].down = False

		self.notDone = True

	def addWall(self, x1, y1, x2, y2):
		# creates wall between the nodes specified by these coordinates
		node1 = self.maze[x1][y1]
		node2 = self.maze[x2][y2]

		if(x1 < 0 or x1 >= self.rows or 
			x2 < 0 or x2 >= self.rows or
			y1 < 0 or y1 >= self.cols or
			y2 < 0 or y2 >= self.cols):
			print("invalid coordinates")
			return
		#walls can only difer in one coordinate
		if(x1 == x2):
			if(math.fabs(y1-y2)!=1):
				print("invalid wall")
			elif(y1 == y2+1):
				#node1 is to the right of node2
				node1.left = False
				node2.right = False
			elif(y2 == y1+1):
				#node2 is to the right of node1
				node2.left = False
				node1.right = False
			else:
				print("invalid wall")
		elif(y1 == y2):
			if(math.fabs(x1-x2)!=1):
				print("invalid wall")
			elif(x1 == x2+1):
				#node1 is below node2
				node1.up = False
				node2.down = False
			elif(x2 == x1+1):
				#node2 is below node1
				node2.up = False
				node1.down = False
			else:
				print("invalid wall")
		else:
			#both coordinates are the same
			print("coordinates must be different")
		return

	def addRandomWalls(self, num):
		for i in range(num):
			row = random.randint(0,self.rows-1)
			col = random.randint(0,self.col-1)
			direction = random.randint(1,4)
			if(direction==1):
				#up
				pass
			elif(direction==2):
				#down
				pass
			elif(direction==3):
				#right
				pass
			elif(direction==4):
				#left
				pass


	def drawMaze(self):
		win = self.win
		for i in range(self.rows):
			for j in range(self.cols):
				rect = Rectangle(Point(j*self.gridSize, i*self.gridSize), 
					Point(j*self.gridSize + self.gridSize, i*self.gridSize +self.gridSize))

				mazeNode = self.maze[i][j]

				if(mazeNode.isCurr):
					rect.setFill("blue")
				elif(mazeNode.visited):
					rect.setFill("red")
				else:
					rect.setFill("white")
				rect.draw(win)
				
				#draw walls
				if(not mazeNode.left):
					#left wall
					wall = Line(Point(j*self.gridSize, i*self.gridSize),
						Point(j*self.gridSize, i*self.gridSize + self.gridSize))
					wall.setWidth(5)
					wall.setFill("brown")
					wall.draw(win)
				if(not mazeNode.right):
					#right wall
					wall = Line(Point(j*self.gridSize+ self.gridSize, i*self.gridSize),
						Point(j*self.gridSize+ self.gridSize, i*self.gridSize + self.gridSize))
					wall.setWidth(5)
					wall.setFill("brown")
					wall.draw(win)
				if(not mazeNode.down):
					#down wall
					wall = Line(Point(j*self.gridSize, i*self.gridSize+ self.gridSize),
						Point(j*self.gridSize+self.gridSize, i*self.gridSize+ self.gridSize))
					wall.setWidth(5)
					wall.setFill("brown")
					wall.draw(win)
				if(not mazeNode.up):
					#up wall
					wall = Line(Point(j*self.gridSize, i*self.gridSize),
						Point(j*self.gridSize+self.gridSize, i*self.gridSize))
					wall.setWidth(5)
					wall.setFill("brown")
					wall.draw(win)
				

		#win.getMouse()
		sleep(0.05)
		#win.close()
		win.update()
			

	def printMaze(self):
		for i in range(self.rows):
			row = ""
			for j in range(self.cols):
				row += self.maze[i][j].toString()
				if(self.maze[i][j].right == False):
					row += "|"
				if(self.maze[i][j].down == False):
					row += "_"
				row += "   "
			print(row+"\n")

	def reset(self):
		for i in range(self.rows):
			for j in range(self.cols):
				self.maze[i][j].reset()
		self.currNode = self.maze[0][0]
		self.currNode.isCurr = True
		self.currNode.visit()

	def BFS(self):
		#start from currNode
		q = queue.Queue()
		q.put(self.currNode)
		while(not q.empty()):
			node = q.get()
			node.visit()
			print("at", node.x, node.y)
			print("left", node.left)
			print("right", node.right)
			print("up", node.up)
			print("down", node.down)
			if(node.up):
				up = self.maze[node.x-1][node.y]
				if(not up.visited):
					print("adding up", node.x-1, node.y)
					q.put(up)
			if(node.right):
				right = self.maze[node.x][node.y+1]
				if(not right.visited):
					print("adding right", node.x, node.y+1)
					q.put(right)
			if(node.left):
				left = self.maze[node.x][node.y-1]
				if(not left.visited):
					print("adding left", node.x, node.y-1)
					q.put(left)
			if(node.down):
				down = self.maze[node.x+1][node.y]
				if(not down.visited):
					print("adding down", node.x+1, node.y)
					q.put(down)
			self.printMaze()

	def DFS(self):
		#start from currNode
		stack = []
		stack.append(self.currNode)
		while(len(stack)!=0):
			node = stack.pop()
			if(not node.visited):
				node.visit()
				self.printMaze()
				self.drawMaze()
				if(node.down):
					down = self.maze[node.x+1][node.y]
					if(not down.visited):
						print("adding down", node.x+1, node.y)
						stack.append(down)
				if(node.up):
					up = self.maze[node.x-1][node.y]
					if(not up.visited):
						print("adding up", node.x-1, node.y)
						stack.append(up)
				if(node.right):
					right = self.maze[node.x][node.y+1]
					if(not right.visited):
						print("adding right", node.x, node.y+1)
						stack.append(right)
				if(node.left):
					left = self.maze[node.x][node.y-1]
					if(not left.visited):
						print("adding left", node.x, node.y-1)
						stack.append(left)
			

if __name__ == '__main__':
	maze = Maze(4,5)
	maze.addWall(0,0,1,0)
	maze.addWall(1,2,1,3)
	#maze.printMaze()
	maze.DFS()

```



