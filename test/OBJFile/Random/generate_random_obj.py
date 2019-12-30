import os
import random

NUM_FACES = 1000
OUTPUT_FILE = 'test_' + str(NUM_FACES) + '.obj'
MAX_FACE_SIZE = 100
RESOLUTIONX = 1000
RESOLUTIONY = 1000
RESOLUTIONZ = 1000

vertices = []

for i in range(0, NUM_FACES):
	offsetX = random.randint(0, RESOLUTIONX - MAX_FACE_SIZE)
	offsetY = random.randint(0, RESOLUTIONY - MAX_FACE_SIZE)
	offsetZ = random.randint(0, RESOLUTIONZ - MAX_FACE_SIZE)
	for j in range(0, 3):
		vertex = [random.random() * MAX_FACE_SIZE + offsetX, random.random() * MAX_FACE_SIZE + offsetY, random.random() * MAX_FACE_SIZE + offsetZ]
		vertices.append(vertex)

with open(OUTPUT_FILE, 'w') as f:
	for vertex in vertices:
		f.write("v " + str(vertex[0]) + " " + str(vertex[1]) + " " + str(vertex[2]) + "\n")
	f.write("\n")
	for i in range(0, NUM_FACES):
		f.write("f " + str(i*3+1) + " " + str(i*3+2) + " " + str(i*3+3) + "\n")