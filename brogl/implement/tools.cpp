#pragma once

#include "../tools.h"
#include "../boilerplate.h"

namespace bro
{
	std::string ReadFile(const char* _filepath)
	{
		// Open input file from filepath
		std::ifstream file(_filepath);
		if (!file.is_open()) { throw std::runtime_error("Couldn't open file"); }
		// Retreive file contents line by line
		std::string data, ln;
		while (std::getline(file, ln)) { data += ln; }
		file.close();
		return data;
	}

	wfobj OpenWFObj(const char* _filepath)
	{
		// Open input file from filepath
		std::ifstream file(_filepath);
		if (!file.is_open()) { throw std::runtime_error("Couldn't open file"); }
		// Wavefront object to generate
		wfobj obj;
		// Raw object data
		std::vector<float> vertices, texcoords, normals;
		std::vector<int> faces;
		// Indexed data to be used for VBOs
		std::vector<float> fVerts, fTexcoords, fNormals;
		// Retreive file contents line by line
		std::string ln;
		while (std::getline(file, ln))
		{
			// Tokenize line
			std::vector<std::string> tokens(1);
			for (char& c : ln)
			{
				// Split on whitespace
				if (c <= 32) { tokens.push_back(""); }
				else 
				{ 				
					// Add nonwhitespace to current token
					tokens.back() += c;
				}

			}

			// Attempt deserialization 
			std::string lntype = tokens.at(0);
			if (lntype == "v")
			{
				vertices.push_back((float)atof(tokens.at(1).c_str())); // x
				vertices.push_back((float)atof(tokens.at(2).c_str())); // y
				vertices.push_back((float)atof(tokens.at(3).c_str())); // z
				// todo: add w optional
			}
			else if (lntype == "vt")
			{
				texcoords.push_back((float)atof(tokens.at(1).c_str())); // u
				texcoords.push_back((tokens.size() > 2 ? 1 - (float)atof(tokens.at(2).c_str()) : 0)); // v
				// todo: add w optional
			}
			else if (lntype == "vn")
			{
				normals.push_back((float)atof(tokens.at(1).c_str())); // x
				normals.push_back((float)atof(tokens.at(2).c_str())); // y
				normals.push_back((float)atof(tokens.at(3).c_str())); // z
			}
			else if (lntype == "f")
			{
				std::vector<std::vector<int>> face(tokens.size() - 1);
				for (size_t i = 0, t = 1; t < tokens.size(); ++i, ++t)
				{
					// Get token string
					std::string& s = tokens.at(t);

					// Tokenize again on slashes
					std::string tk = "";
					for (char& c : s)
					{
						// Deserialize on slashes
						if (c == '/')
						{
							face.at(i).push_back((tk != "" ? atoi(tk.c_str()) : -1));
							tk = "";
						}
						else
						{
							// Add nonslashes to token
							tk += c;
						}
					}
					// See if there are normals on the end
					face.at(i).push_back((tk != "" ? atoi(tk.c_str()) : -1));
				}

				// Append face to faces vector
				for (size_t i = 0; i < face.size(); ++i)
				{
					for (int& f : face.at(i))
					{
						faces.push_back(f);
					}
				}
				// Append nulls to faces if not quad
				if (face.size() < 4)
				{
					faces.insert(faces.end(), { -1, -1, -1 });
				}
			}
		}

		// Close source obj file
		file.close();

		// Assemble object, todo: use 'o' to group parts for v/vt/vn separation
		const int quadindex[3]{ 2, 3, 0 };
		for (size_t i = 0; i < faces.size(); i += 12)
		{
			// Vertex indices
			int v[4]{ (faces.at(i) - 1) * 3, (faces.at(i + 3) - 1) * 3, (faces.at(i + 6) - 1) * 3, (faces.at(i + 9) - 1) * 3 };
			// Texcoord indices
			int vt[4]{ (faces.at(i + 1) - 1) * 2, (faces.at(i + 4) - 1) * 2, (faces.at(i + 7) - 1) * 2, (faces.at(i + 10) - 1) * 2 };
			// Normal indices
			int vn[4]{ (faces.at(i + 2) - 1) * 3, (faces.at(i + 5) - 1) * 3, (faces.at(i + 8) - 1) * 3, (faces.at(i + 11) - 1) * 3 };
			// Flags
			bool isQuad = (v[3] > -1);

			// Insert final triangle vertex data
			for (size_t j = 0; j < 3; ++j)
			{
				fVerts.insert(fVerts.end(), { vertices.at(v[j]), vertices.at(v[j] + 1), vertices.at(v[j] + 2) });
				fTexcoords.insert(fTexcoords.end(), { texcoords.at(vt[j]), texcoords.at(vt[j] + 1) });
				fNormals.insert(fNormals.end(), { normals.at(vn[j]), normals.at(vn[j] + 1), normals.at(vn[j] + 2) });
				obj.verticesCount++;
			}
			// Add extra triangle for quads, todo: maybe create an index buffer instead
			if (isQuad) 
			{ 
				for (size_t j = 0; j < 3; ++j)
				{
					const size_t q = quadindex[j];
					fVerts.insert(fVerts.end(), { vertices.at(v[q]), vertices.at(v[q] + 1), vertices.at(v[q] + 2) });
					fTexcoords.insert(fTexcoords.end(), { texcoords.at(vt[q]), texcoords.at(vt[q] + 1) });
					fNormals.insert(fNormals.end(), { normals.at(vn[q]), normals.at(vn[q] + 1), normals.at(vn[q] + 2) });
					obj.verticesCount++;
				}
			} 

		}

		// Push data to vertex buffers 
		obj.vertices = CreateVBO(fVerts.size() * sizeof(float), fVerts.data());
		obj.texcoords = CreateVBO(fTexcoords.size() * sizeof(float), fTexcoords.data());
		obj.normals = CreateVBO(fNormals.size() * sizeof(float), fNormals.data());

		return obj;
	}

}