/*
Generated By HoudiniSolverGenerator
Author: MuGdxy https://github.com/MuGdxy
*/

#include <GU/GU_PrimPoly.h>
#include <PRM/PRM_Include.h>
#include <SIM/SIM_DopDescription.h>
#include <SIM/SIM_GeometryCopy.h>
#include <SIM/SIM_DataFilter.h>
#include <SIM/SIM_Object.h>
#include <SIM/SIM_ObjectArray.h>
#include <SIM/SIM_Engine.h>
#include <SIM/SIM_Force.h>
#include "SIM__EXAMPLE_SOLVER_.h"
#include "AttribHelper.h"

SIM_Solver::SIM_Result
_EXAMPLE_SOLVER_Wrapper::Init(SolverArgs args)
{
	std::cout << "_EXAMPLE_SOLVER_ Init" << std::endl;
	auto* geo = SIM_DATA_CREATE(
		args.object, "Geometry", SIM_GeometryCopy, SIM_DATA_RETURN_EXISTING | SIM_DATA_ADOPT_EXISTING_ON_DELETE);

	// Read Geometry
	{
		SIM_GeometryAutoWriteLock lock(geo);
		GU_Detail& gdp = lock.getGdp();

		auto  prims = gdp.primitives();
		auto  primCount = prims.entries();

		auto invMass = PointAttribute<GA_ROHandleF>(gdp, "invMass");
		auto validInvMass = invMass.isValid();

		// get points
		auto points = gdp.getNumPoints();
		for (size_t i = 0; i < points; i++)
		{
			auto offset = gdp.pointOffset(i);
			auto pos = gdp.getPos3(offset);
			// set to your own solver

			if (validInvMass)
			{
				auto invM = invMass.get(offset);
				// set to your own solver
			}
		}

		// ...
	}

	// External Collision may comes from affectors
	SIM_ObjectArray affectors;
	args.object.getAffectors(affectors, "SIM_RelationshipSource");
	auto n = affectors.entries();
	for (size_t i = 0; i < n; i++)
	{
		auto affector = affectors(i);
		if(affector->getName() == "XXXX") // if it's your collider
		{
			auto* geo = SIM_DATA_GET(*affector, "Geometry", SIM_GeometryCopy);
			SIM_GeometryAutoWriteLock lock(geo);
			GU_Detail& gdp = lock.getGdp();

			//... read geo
		}
	}
	return SIM_Solver::SIM_Result::SIM_SOLVER_SUCCESS;
}

SIM_Solver::SIM_Result
_EXAMPLE_SOLVER_Wrapper::Solve(SolverArgs args)
{
	std::cout << "_EXAMPLE_SOLVER_ Solve" << std::endl;
	auto* geo = SIM_DATA_GET(args.object, "Geometry", SIM_GeometryCopy);

	// Read Geometry (If needed)

	// Run Simulation

	// Write Geometry Back
	{
		SIM_GeometryAutoWriteLock lock(geo);
		GU_Detail& gdp = lock.getGdp();
		auto pointCount = gdp.getNumPoints();
		auto vAttr = gdp.addFloatTuple(GA_AttributeOwner::GA_ATTRIB_POINT, "v", 3);
		auto vHandle = GA_RWHandleV3(vAttr);

		// write sim geometry points
		auto points = gdp.getNumPoints();
		for (size_t i = 0; i < points; i++)
		{
			auto offset = gdp.pointOffset(i);
			// x v from your own solver
			UT_Vector3 x, v;
			gdp.setPos3(offset, x);
			vHandle.set(offset, v);
		}
	}

	return SIM_Solver::SIM_Result::SIM_SOLVER_SUCCESS;
}