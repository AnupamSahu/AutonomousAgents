#pragma once

#include <CoreMinimal.h>
#include <Math/MathFwd.h>

#include "GridConfiguration.h"
#include "SpatialGridSubsystem.generated.h"

// This should ideally be 64 since we use a 64-bit unsigned integer, but may vary to support other sizes. 
constexpr int GBitRowSize = 64;

/**
* Number of integers in a BitBlock. Use a larger number to support more agents.
* E.g : with GBitRowSize of 64, and GBlockSize of 20 the spatial grid can only handle 64 * 20 that is 1280 agents.
*/
constexpr int GBlockSize = 100;

// Represents a location on the grid in terms of Column and Row Indices.
struct FGridCellLocation
{
	FGridCellLocation()
		: X(0), Y(0)
	{}
	
	FGridCellLocation(const int XIndex, const int YIndex)
		: X(XIndex), Y(YIndex)
	{}

	bool operator==(const FGridCellLocation& Other) const
	{
		return Other.X == X && Other.Y == Y;		
	}

	bool operator!=(const FGridCellLocation& Other) const
	{
		return !operator==(Other);
	}
	
	int X; // Row Index
	int Y; // Column Index
};

struct FGridAgent
{
	FVector Location;
	FGridCellLocation GridCellLocation;
};

// Wrapper over an Array of 64-bit Integers.
struct FBitBlock
{
	FBitBlock()
	{
		BitRow.Init(0, GBlockSize);
	}

	uint64& operator[](const uint32 Index)
	{
		return BitRow[Index];
	}
	
	const uint64& operator[](const uint32 Index) const
	{
		return BitRow[Index];
	}

	TArray<uint64, TInlineAllocator<GBlockSize>> BitRow;
};

/**
 * The SpatialGridSubsystem implements an implicit spatial grid
 * that keeps track of the location of agents
 * and provides a fast lookup feature to find agents in a certain region.
 * 
 * Each dimension has its own array of BitBlocks. A BitBlock is basically a fixed size array of 64-bit unsigned integers.
 * The current implementation of the SpatialGrid supports two dimensions (X & Y) only.
 *
 * The SpatialGrid captures the world location of agents and maps their indices into corresponding BitBlocks.
 */
UCLASS()
class SPATIALGRID_API USpatialGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief Reserves and initializes arrays with 0's.
	 * @param NewConfiguration The configuration UDataAsset that the subsystem must use to get all its configuration information.
	 */
	UFUNCTION(BlueprintCallable)
	void InitializeGrid(const UGridConfiguration* NewConfiguration);

public:
	
	/**
	 * @brief Puts a new agent into the grid.
	 */
	void AddAgent(const FVector& Location);

	/**
	 * @brief Finds all agents in an area of the Grid.
	 * @param Location Center of the search region.
	 * @param Radius Radius of the search region.
	 * @param Out_AgentIndices Output vector of indices of agents that were found.
	 */
	void FindNearbyAgents(const FVector& Location, const float Radius, TArray<uint32>& Out_AgentIndices) const;

	/**
	 * @brief Draws lines in the world space to visualize the grid.
	 */
	void DrawGrid() const;

	/**
	 * @brief Highlights a valid cell in the grid.
	 * @param GridLocation GridLocation in terms of Row and Column Indices.
	 */
	void TryDrawCell(const FGridCellLocation& GridLocation) const;

	void UpdateSingleAgent(uint32 AgentIndex, const FVector& NewLocation);

	void UpdateAllAgents(const TArray<FVector>& NewLocations);

protected:
	
	/**
	 * @brief Returns indices of all agents present in a certain cell in the Grid.
	 * @param GridLocation Location of the cell in the Grid.
	 * @param Out_Indices Output vector of indices of agents that were found.
	 */
	virtual void GetIndicesInGridLocation(const FGridCellLocation& GridLocation, TArray<int>& Out_Indices) const;

	// Converts world-space location to a location of a cell in the grid.
	bool ConvertWorldToGridLocation(FVector WorldLocation, FGridCellLocation& Out_GridLocation) const;

	// Converts a location of a cell in the grid to a world-space location.
	bool ConvertGridToWorldLocation(const FGridCellLocation& GridLocation, FVector& Out_WorldLocation) const;

	// Checks if a given world-space location lies within the bounds of the grid. 
	virtual bool IsValidWorldLocation(const FVector& WorldLocation) const;

	// Checks if a given grid location has indices that lie within the bounds of block arrays.
	virtual bool IsValidGridLocation(const FGridCellLocation& GridLocation) const;

	// Fills all block arrays with 0s.
	virtual void RemoveIndexFromCell(const uint32 AgentIndex, const FGridCellLocation& GridCellLocation);

protected:

	/**
	* Total number of blocks in either Rows or columns.
	* Since the Grid is designed to be a 2-D Square, number of row and column blocks is the same.
	*/
	uint32 NumBlocks;

	// Agents being actively tracked in the grid.
	TArray<FGridAgent> GridAgents;

	/**
	* Reference to a UDataAsset that is essential for initializing the
	* Grid with importance information like size and resolution.
	*/
	UPROPERTY(Transient)
	const UGridConfiguration* GridParameters;

	// An array of BitBlocks (stack of 64-bit integers) that register indices of agents based on their X-Coordinate.
	TArray<FBitBlock> RowBlocks;
	
	/**
	* An array of BitBlocks (stack of 64-bit integers) that register
	* indices of agents based on their Y-Coordinate. Each dimension has its own array of BitBlocks.
	* The current implementation of the SpatialGrid supports two dimensions (X & Y) only.
	*/
	TArray<FBitBlock> ColumnBlocks;

};