#include "pHash_cpp_wrapper.h"

using namespace std;

bool TextHash_Wrapper::ph_texthash(const string &filename)
{
	int npoints;
	TxtHashPoint* p = ::ph_texthash(filename.c_str(), &npoints);
	if (p == NULL)
		return false;
	PopulateSelf(npoints, p);
	return true;
}

ostream&  operator << (ostream& o, const TextHash_Wrapper& pw)
{
	unsigned int n = pw.npoints;
	if (pw.assigned)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			o << pw.phash_vec[i].hash << "\t";
		}
	}
	return o;
}


bool TextHash_Wrapper::ph_compare_text_hashes(const TextHash_Wrapper *thw1,
	const TextHash_Wrapper *thw2, TextMatch_Wrapper* result_out)
{
	int nmatches;
	TxtMatch* tm = ::ph_compare_text_hashes(thw1->phash_vec, thw1->npoints,
		thw2->phash_vec, thw2->npoints,&nmatches);
	unsigned int na = thw1->GetNPoints();
	unsigned int nb = thw2->GetNPoints();
	result_out->SetValues(nmatches, tm,na,nb);
	return true;
}

void TextMatch_Wrapper::SetValues(int nmatches_, TxtMatch* arr_,unsigned int na_, unsigned int nb_)
{
	if (assigned)
	{
		Destroy();
	}
	assigned = true;
	nmatches = nmatches_;
	matches = arr_;
	na = na_;
	nb = nb_;
}


std::ostream&  operator << (std::ostream& o, const TextMatch_Wrapper& pw)
{
	unsigned int n = pw.nmatches;
	if (pw.assigned)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			o << pw.matches[i].length << "\t";
			o << pw.matches[i].first_index << "\t";
			o << pw.matches[i].second_index << "\t";
			o << endl;
		}
	}
	return o;
}

//ruby code from https://github.com/toy/pHash/blob/master/lib/phash/text.rb
//
//matches_length_p = FFI::MemoryPointer.new :int
//if data = ph_compare_text_hashes(hash_a.data, hash_a.length, hash_b.data, hash_b.length, matches_length_p)
	//matches_length = matches_length_p.get_int(0)
	//matches_length_p.free
	//
	//matches = matches_length.times.map{ | i | TxtMatch.new(data + i * TxtMatch.size) }
	//
	//matched_a = Array.new(hash_a.length)
	//matched_b = Array.new(hash_b.length)
	//matches.each do | match |
		//index_a = match[:index_a]
		//index_b = match[:index_b]
		//match[:length].times do | i |
			//matched_a[index_a + i] = true
			//matched_b[index_b + i] = true
		//end
	//end
	//coverage_a = matched_a.compact.length / hash_a.length.to_f
	//coverage_b = matched_b.compact.length / hash_b.length.to_f
	//
	//similarity = (coverage_a + coverage_b) * 0.5

double TextMatch_Wrapper::GetSimilarity() //based on the ruby code above
{
	unsigned int total_matches = 0;
	/*for (unsigned int i = 0; i < nmatches; i++)
	{
		total_matches += matches[i].length;
	}*/
	total_matches = GetNMatches();
	double coverage_a = (double)total_matches / (double)na;
	double coverage_b = (double)total_matches / (double)nb;
	return (coverage_a + coverage_b) * 0.5;
}
