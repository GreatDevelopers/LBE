
all: lakaEngine 

lakaEngine:	session.o laka_engine.o auth.o user.o post_loop.o post_pad.o add_theme.o dashboard.o setting_pannel.o category_pannel.o 
	g++ session.o laka_engine.o auth.o user.o post_loop.o post_pad.o add_theme.o dashboard.o setting_pannel.o category_pannel.o -o lakaEngine  -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lwtdbo -lwtdbosqlite3

session.o: session.C
	g++ -Wall -std=c++0x -c session.C

laka_engine.o: laka_engine.C
	g++ -Wall -std=c++0x -c laka_engine.C

auth.o: auth.C
	g++ -Wall -std=c++0x -c auth.C

user.o: user.C
	g++ -Wall -std=c++0x -c user.C

post_loop.o: post_loop.C
	g++ -Wall -std=c++0x -c post_loop.C

post_pad.o: admin/post_pad.C
	g++ -Wall -std=c++0x -c admin/post_pad.C

add_theme.o: add_theme.C
	g++ -Wall -std=c++0x -c add_theme.C

dashboard.o: admin/dashboard.C
	g++ -Wall -std=c++0x -c admin/dashboard.C

setting_pannel.o: admin/setting_pannel.C
	g++ -Wall -std=c++0x -c admin/setting_pannel.C

category_pannel.o: admin/category_pannel.C
	g++ -Wall -std=c++0x -c admin/category_pannel.C

clean:
	 rm -rf *.o lakaEngine

run:
	./lakaEngine --docroot . --http-address 0.0.0.0 --http-port 1313 
