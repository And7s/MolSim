/*
 * filereader.cxx
 * shows the use of the given xsd input
 *  Created on: 24.11 .2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include <memory>   // std::auto_ptr
#include <iostream>

#include "input.hxx"

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " hello.xml" << endl;
    return 1;
  }

  try
  {
    auto_ptr<hello_t> h (hello (argv[1]));

    for (hello_t::name_const_iterator i (h->name ().begin ());
         i != h->name ().end ();
         ++i)
    {
      cout << h->greeting () << ", " << *i << "!" << endl;
     // cout << h->base_name_output_file() << " : | "<< endl;
    }
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
}
