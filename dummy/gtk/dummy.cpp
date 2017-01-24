//sudo apt-get install libgtkmm-3.0-dev
//Archlinux : gtkmm3
//g++ dummy.cpp `pkg-config gtkmm-3.0 --cflags --libs`
//ou
//g++ -std=c++11 dummy.cpp $(pkg-config --cflags --libs gtkmm-3.0)

#include <iostream>
#include <cstdlib>
#include <gtkmm.h>
#include <string>

int main(int argc, char* argv[]) {

	int hp1 = 42, hp2 = 42;

	// création de la fenêtre
	auto app = Gtk::Application::create(argc, argv);
	Gtk::Window w;
	w.set_default_size(800, 480);
	w.set_title("dummy");

	// ajout des boutons
		// container
		Gtk::Box c;

		// player 1
		Gtk::Box p1;
		p1.property_orientation() = Gtk::ORIENTATION_VERTICAL;
		Gtk::Label l1;
		l1.set_text(std::to_string(hp1));
		p1.pack_start(l1);
		Gtk::Box b1;
		b1.property_orientation() = Gtk::ORIENTATION_VERTICAL;
		Gtk::Button p1_heal_1;
		Gtk::Button p1_heal_7;
		Gtk::Button p1_heal_33;
		Gtk::Button p1_hit_1;
		Gtk::Button p1_hit_7;
		Gtk::Button p1_hit_33;
		p1_heal_1.add_label("heal 1");
		p1_heal_7.add_label("heal 7");
		p1_heal_33.add_label("heal 33");
		p1_hit_1.add_label("hit 1");
		p1_hit_7.add_label("hit 7");
		p1_hit_33.add_label("hit 33");
		b1.pack_start(p1_heal_33);
		b1.pack_start(p1_heal_7);
		b1.pack_start(p1_heal_1);
		b1.pack_start(p1_hit_33);
		b1.pack_start(p1_hit_7);
		b1.pack_start(p1_hit_1);
		p1.pack_start(b1);
			// gestion des events
			p1_heal_1.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1++)); });
			p1_heal_7.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1+=7)); });
			p1_heal_33.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1+=33)); });
			p1_hit_1.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1--)); });
			p1_hit_7.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1-=7)); });
			p1_hit_33.signal_clicked().connect([&hp1, &l1]{ l1.set_text(std::to_string(hp1-=33)); });
		c.pack_start(p1);
	
		// player 2
		Gtk::Box p2;
		p2.property_orientation() = Gtk::ORIENTATION_VERTICAL;
		Gtk::Label l2;
		l2.set_text(std::to_string(hp2));
		p2.pack_start(l2);
		Gtk::Box b2;
		b2.property_orientation() = Gtk::ORIENTATION_VERTICAL;
		Gtk::Button p2_heal_1;
		Gtk::Button p2_heal_7;
		Gtk::Button p2_heal_33;
		Gtk::Button p2_hit_1;
		Gtk::Button p2_hit_7;
		Gtk::Button p2_hit_33;
		p2_heal_1.add_label("heal 1");
		p2_heal_7.add_label("heal 7");
		p2_heal_33.add_label("heal 33");
		p2_hit_1.add_label("hit 1");
		p2_hit_7.add_label("hit 7");
		p2_hit_33.add_label("hit 33");
		b2.pack_start(p2_heal_33);
		b2.pack_start(p2_heal_7);
		b2.pack_start(p2_heal_1);
		b2.pack_start(p2_hit_33);
		b2.pack_start(p2_hit_7);
		b2.pack_start(p2_hit_1);
		p2.pack_start(b2);
			// gestion des events
			p2_heal_1.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2++)); });
			p2_heal_7.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2+=7)); });
			p2_heal_33.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2+=33)); });
			p2_hit_1.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2--)); });
			p2_hit_7.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2-=7)); });
			p2_hit_33.signal_clicked().connect([&hp2, &l2]{ l2.set_text(std::to_string(hp2-=33)); });
		c.pack_start(p2);

	w.add(c);
	w.show_all_children();
	return app->run(w);
}
