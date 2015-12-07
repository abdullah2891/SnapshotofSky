import serial
import sys 
import time 

def xbee_reading():
        #Port=sys.argv[1]
        Port='COM3'
        buffer_clear=0
        p=0;
        q=0;
        ser = serial.Serial(port=Port,baudrate=57600)
        counter=0
        string=""
        outlist=[];
        msb=0;
        lsb=0;
        formatter=0
        position=[];
        reading=0
        l=[]

        a=time.time()
        while counter<57 :
                
                #print buffer_clear
                s=ser.read()
                n=float(ord(s))
                #print(n)
                if(n==126):
                    counter=0;
                    #print "---------- Timestamp: "+str(time.time())+"-----------------"
                    buffer_clear=0
                    formatter=0
                    position=[];
                                   
                counter=counter+1
                
                
            
                if counter>=19 :
                        
                        rem=(counter-18)%2
                        
                        if(rem==1):
                                msb=n
                              
                        if(rem==0):
                                lsb=n
                                
                                #print str(msb)+"    "+str(lsb)+ "  "+str(counter)
                                reading=(msb*256)+lsb
                                if(reading<=1023):
                                       # reading=#5.0*(reading/1023.0)
                                        #print str(lsb)+"    "+str(msb)+"  "+str( len(outlist))+'\n' 
                                        string+=str(reading)+"  "
                                        outlist+=[reading]
                                        buffer_clear+=1
                                else:
                                        string+=str(p)+"  "
                        p=reading
   
                        
          
                                        
                #print len(outlist)
                         
        
        ser.close()
       
       
        #return outlist   #+[position]
        return string



def __main__():
        s=xbee_reading();
                
        #print len(s.split()) 
        sys.stdout.write(s)
        
__main__()

