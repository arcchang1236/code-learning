import os
import subprocess
import sys
id = raw_input("Please enter your student id:")
hidden_list=[]
student_list=[]
test_list=[]
htpath = "/home/archi/s"+str(id) + "/Archi2016_Project1/" + str(id) +"_01/testing/hidden_testcase"
stpath = "/home/archi/s"+str(id) + "/Archi2016_Project1/" + str(id) +"_01/testing/student_testcase"
tpath  = "/home/archi/s"+str(id) + "/Archi2016_Project1/" + str(id) +"_01/testing/tests"
print htpath
for dirP,dirN,FN in os.walk(htpath):
	hidden_list.append(dirP)
for dirP,dirN,FN in os.walk(stpath):
	student_list.append(dirP)
for dirP,dirN,FN in os.walk(tpath):
	test_list.append(dirP)
def file_test(file_list):
	for filepath in file_list:
		if(filepath != file_list[0]):
			ipath = filepath+'/'+'iimage.bin'
			dpath = filepath+'/'+'dimage.bin'
			if( os.path.isfile and  os.path.isfile(dpath)):
				print ("Files exist") 
			icom = 'cp ' + ipath+' .'
			dcom = 'cp ' + dpath+' .'
			icp = os.system(icom)
			dcp = os.system(dcom)
			if(icp ==0 and  dcp ==0):
				print ("copy correct")
			ifilename = filepath.split('/',8)[8]
			subprocess.call(['make','clean'],shell=False,stdout = subprocess.PIPE)
			subprocess.call('make',shell=False,stdout = subprocess.PIPE)
			os.system('./single_cycle')
			idiffcom = 'diff '+'snapshot.rpt '+filepath+'/'+'snapshot.rpt' 
			idiff = os.system(idiffcom)
			if(idiff ==0):
				print ("Snapshot Correct!")
			else:
				print ("Error or Wrong")
				print 'testing :' +ifilename
				return ;
			ddiffcom = 'diff '+'error_dump.rpt '+filepath+'/'+'error_dump.rpt'
			ddiff = os.system(ddiffcom)
			if(ddiff==0):
				print ("Error_dump Correct!")
			else:
				print ("Error or Wrong")	
				print 'testing :' +ifilename
				return ;
			print 'testing :' +ifilename
print "start:" +hidden_list[0]
file_test(hidden_list)
print "start:" +student_list[0]
file_test(student_list)
print "start:" +test_list[0]
file_test(test_list)
