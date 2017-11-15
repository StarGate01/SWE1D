/**
 * @file VtkWriter.hpp
 * @brief Writes data to a XML-based VTK file
 */

#ifndef VTKWRITER_H_
#define VTKWRITER_H_

#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include "../types.hpp"

namespace writer
{

	/**
	 * @brief A writer class that generates vtk files
	 */
	class VtkWriter
	{

	private:

		/** @brief Base name of the vtp collectiond and vtk files */
		std::string m_basename;

		/** @brief Cell size */
		T m_cellSize;

		/** @brief Current time step */
		unsigned int m_timeStep;

		/** @brief VTP stream */
		std::ofstream *m_vtpFile;


	public:

		/**
		 * @brief Constructor
		 * 
		 * @param basename The filename of the output file without extension
		 * @param cellSize The size of a cell
		 */
		VtkWriter( const std::string& basename = "swe1d", const T cellSize = 1) : m_basename(basename), m_cellSize(cellSize), m_timeStep(0)
		{
			// initialize vtp stream
			std::ostringstream l_vtpFileName;
			l_vtpFileName << m_basename << ".vtp";
			m_vtpFile = new std::ofstream( l_vtpFileName.str().c_str() );

			// write vtp header
			*m_vtpFile
				<< "<?xml version=\"1.0\"?>" << std::endl
				<< "<VTKFile type=\"Collection\" version=\"0.1\">" << std::endl
				<< "<Collection>" << std::endl;
		}

		/**
		 * @brief Destructor
		 */
		~VtkWriter() {
			// close vtp file
			*m_vtpFile
				<< "</Collection>" << std::endl
				<< "</VTKFile>" << std::endl;
			delete m_vtpFile;	
		}

		/**
		 * @brief Writes all values to vtk file
		 *
		 * @param time Current time
		 * @param h Current height
		 * @param hu Current flux
		 * @param b Current bathymetry
		 * @param f Current frode number
		 * @param size Number of cells (without boundary values)
		 */
		void write(const T time, const T *h, const T *hu, const T *b, const T *f, unsigned int size)
		{
			// generate vtk file name
			std::string l_fileName = generateFileName();

			// add current time to vtp collection
			*m_vtpFile << "<DataSet timestep=\""
						<< time
						<< "0\" group=\"\" part=\"0\" file=\""
						<< l_fileName
						<< "\"/> " << std::endl;

			// write vtk file
			std::ofstream vtkFile(l_fileName.c_str());
			assert(vtkFile.good());

			// vtk xml header
			vtkFile << "<?xml version=\"1.0\"?>" << std::endl
					<< "<VTKFile type=\"RectilinearGrid\">" << std::endl
					<< "<RectilinearGrid WholeExtent=\"0 " << size
						<< " 0 0 0 0\">" << std::endl
					<< "<Piece Extent=\"0 " << size
						<< " 0 0 0 0\">" << std::endl;

			vtkFile << "<Coordinates>" << std::endl
				<< "<DataArray type=\"Float32\" format=\"ascii\">" << std::endl;

			// grid points
			for (int i=0; i < size+1; i++)
				vtkFile << m_cellSize * i << "" << std::endl;

			vtkFile << "</DataArray>" << std::endl;

			vtkFile	<< "<DataArray type=\"Float32\" format=\"ascii\">" << std::endl
					<< "0" << std::endl
					<< "</DataArray>" << std::endl;

			vtkFile	<< "<DataArray type=\"Float32\" format=\"ascii\">" << std::endl
					<< "0" << std::endl
					<< "</DataArray>" << std::endl;

			vtkFile << "</Coordinates>" << std::endl;

			vtkFile << "<CellData>" << std::endl;

			// water surface height
			vtkFile << "<DataArray Name=\"h\" type=\"Float32\" format=\"ascii\">" << std::endl;
			for (int i=1; i < size+1; i++) vtkFile << h[i] << std::endl;
			vtkFile << "</DataArray>" << std::endl;

			// momentum
			vtkFile << "<DataArray Name=\"hu\" type=\"Float32\" format=\"ascii\">" << std::endl;
			for (int i=1; i < size+1; i++) vtkFile << hu[i] << std::endl;
			vtkFile << "</DataArray>" << std::endl;

			// bathymetry
			vtkFile << "<DataArray Name=\"b\" type=\"Float32\" format=\"ascii\">" << std::endl;
			for (int i=1; i<size+1; i++) vtkFile << b[i] << std::endl;
			vtkFile << "</DataArray>" << std::endl;

			// bathymetry + water height
			vtkFile << "<DataArray Name=\"b+h\" type=\"Float32\" format=\"ascii\">" << std::endl;
			for (int i=1; i<size+1; i++) vtkFile << b[i] + h[i] << std::endl;
			vtkFile << "</DataArray>" << std::endl;

			// frode number
			vtkFile << "<DataArray Name=\"f\" type=\"Float32\" format=\"ascii\">" << std::endl;
			for (int i=1; i<size+1; i++) vtkFile << f[i] << std::endl;
			vtkFile << "</DataArray>" << std::endl;

			vtkFile << "</CellData>" << std::endl
					<< "</Piece>" << std::endl;

			vtkFile << "</RectilinearGrid>" << std::endl
					<< "</VTKFile>" << std::endl;

			// increment time step
			m_timeStep++;
		}

	private:

		/**
		 * @brief Generates a vtr file name
		 * 
		 * @return The generated filename containing the time step and the real name
		 */
		std::string generateFileName()
		{
			std::ostringstream name;
			name << m_basename << '_' << m_timeStep << ".vtr";
			return name.str();
		}
		
	};

}

#endif /* VTKWRITER_H_ */
