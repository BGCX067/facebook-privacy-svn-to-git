#! /usr/bin/python

#function to save the dictionary in the memory
def readFile(fileHandle, dictName):
	line = fileHandle.readline() 
	dictName = {} 
    	keycounter = 1 

    	while line: 
		#print line
	        dictName[line[:-1]] = keycounter 
	        keycounter = keycounter + 1 
	        line = fileHandle.readline() 

#	print dictName['901']
	#print  dictName['519447911']
	dicF.close()
    	return dictName


#function to read relationships
def readFriendship(fileHandle, dictionary):

	#write file
	writeF = open("../graph/friendship_right","w+")

	line = fileHandle.readline()
	result=""
	while line:
		for iten in line.split():
			result+= str(dictionary[str(iten)]) + " " 
		#print result[:-1]
		writeF.write(result[:-1]+ "\n")
		line = fileHandle.readline()	
		result=""
	
	fileHandle.close()
	writeF.close()

# Creating the dictionary
dictionary={}
dicF= open("../graph/ord_uniq","r")
dictionary = readFile(dicF,dictionary)

# Ready to translate each friendship
friendship= open("../graph/friendship_fb","r")
readFriendship(friendship,dictionary)



