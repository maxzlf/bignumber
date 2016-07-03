
obj= bigNumber.o main.o

bigNumber:$(obj)
	cc  $(obj) -o bigNumber

bigNumber.o:common_file.h bigNumber.h	
main.o:bigNumber.h

.PHONY:clean
clean:
	-rm $(obj)


