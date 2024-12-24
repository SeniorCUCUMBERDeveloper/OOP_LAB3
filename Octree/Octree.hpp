#ifndef OCTREE_HPP
#define OCTREE_HPP


#include <vector>
#include <iostream>
#include <algorithm>
#include "ContainerPosition.hpp"
#include <tuple>
#include <stack>
#include <memory>
#include <type_traits>
#include <regex>
#define MAX_ITEMS 4

/**
 * @concept PointConcept
 * @brief Concept that requires a point type to have x, y, z coordinates.
 * 
 * This concept requires that a type T has members x, y, z, is comparable with
 * other instances of the same type, and supports division by 2.
 */

template<typename T>
concept PointConcept = requires(T a) {
    { a.x };
    { a.y };
    { a.z };
    { a == std::declval<T>() } -> std::same_as<bool>;
    { a < std::declval<T>() } -> std::same_as<bool>;
    { a.x / 2 } -> std::same_as<decltype(a.x)>;
    { a.y / 2 } -> std::same_as<decltype(a.y)>;
    { a.z / 2 } -> std::same_as<decltype(a.z)>;
};
/**
 * @concept CompatibleCoordinatesPointer
 * @brief Concept that checks if a point can be added to a structure pointed by SizeType.
 *
 * This checks if the point can have coordinates compatible with the dimensions of 
 * the structure pointed to by SizeType.
 */

template<typename PointType, typename SizeType>
concept CompatibleCoordinatesPointer = requires(PointType p, SizeType s) {
    { p.x + s->getLength() } -> std::convertible_to<decltype(p.x)>;
    { p.x == s->getLength() } -> std::convertible_to<bool>;
    { p.y + s->getWidth() } -> std::convertible_to<decltype(p.x)>;
    { p.y == s->getWidth() } -> std::convertible_to<bool>;
    { p.z + s->getHeight() } -> std::convertible_to<decltype(p.x)>;
    { p.z == s->getHeight() } -> std::convertible_to<bool>;
};


/**
 * @concept CompatibleCoordinates
 * @brief Concept that checks if a point can be added to a structure.
 *
 * This checks if the dimensions of the structure are compatible with the point coordinates.
 */

template<typename PointType, typename SizeType>
concept CompatibleCoordinates = requires(PointType p, SizeType s) {
    { p.x + s.getLength() } -> std::convertible_to<decltype(p.x)>;
    { p.x == s.getLength() } -> std::convertible_to<bool>;
    { p.y + s.getWidth() } -> std::convertible_to<decltype(p.x)>;
    { p.y == s.getWidth() } -> std::convertible_to<bool>;
    { p.z + s.getHeight() } -> std::convertible_to<decltype(p.x)>;
    { p.z == s.getHeight() } -> std::convertible_to<bool>;
};


/**
 * @concept CanAdd
 * @brief Concept that combines point and dimension concepts.
 *
 * This checks if a point can be added to a structure with compatible coordinates.
 */

template<typename PointType, typename SizeType>
concept CanAdd = PointConcept<PointType> &&  
                 (CompatibleCoordinates<PointType, SizeType> || CompatibleCoordinatesPointer<PointType, SizeType>);

/**
 * @concept BoundingBoxConcept
 * @brief Concept that checks if a type can represent a bounding box.
 *
 * A bounding box type must satisfy the PointConcept.
 */

template<typename T>
concept BoundingBoxConcept = PointConcept<T>;

/**
 * @struct BoundingBox
 * @brief A structure representing a bounding box in 3D space.
 *
 * @tparam T Type representing points in 3D space.
 */

template <typename T>
requires BoundingBoxConcept<T>
struct BoundingBox{
    T min, max;
    BoundingBox(const T& m, const T& ma) : min(m), max(ma) {}
    /**
     * @brief Check if a point is contained within the bounding box.
     * @param p Point to check.
     * @return True if the point is within the bounding box, otherwise false.
     */
    bool contains(T& p) const {
        return min.x < p.x && p.x < max.x && min.y < p.y && p.y < max.y && min.z < p.z && p.z < max.z;
    }
    /**
     * @brief Check if the bounding box is valid based on a minimum size.
     * @param minSize Minimum allowed size for the bounding box.
     * @return True if the bounding box is valid, otherwise false.
     */
    bool isValid(const decltype(T::x) minSize) const {
        decltype(auto) width = max.x - min.x;
        decltype(auto) height = max.y - min.y;
        decltype(auto) depth = max.z - min.z;
        return width > minSize && height > minSize && depth > minSize;
    }

};

/**
 * @class Octree
 * @brief A spatial partitioning structure that organizes points in 3D space.
 * 
 * @tparam T Type representing points in 3D space.
 * @tparam N Type associated with the objects to be stored in the octree.
 */

template <typename T, typename N>
//requires BoundingBoxConcept<T> && CanAdd<T, N>
class Octree{
    public:
        struct Node{
            std::vector<std::pair<ContainerPosition<T>, N>> con;
            std::array<std::shared_ptr<Node>, 8> children;
            BoundingBox<T> box;
            std::weak_ptr<Node> parent;
            Node(BoundingBox<T> box) : box(box) {}
            /**
             * @brief Check if the node is a leaf node (has no children).
             * @return True if it is a leaf node, otherwise false.
             */
            bool isLeaf() const {
               return std::all_of(children.begin(), children.end(), [](const std::shared_ptr<Node>& child) { return child == nullptr; });
            }
            /**
             * @brief Get container data stored in this node.
             * @return Vector of container positions and associated data.
             */
            std::vector<std::pair<ContainerPosition<T>, N>> getCon(){
                return con;
            }

        };

    /**
     * @class BidirectionalIterator
     * @brief A bidirectional iterator for traversing the octree nodes.
     */

    class BidirectionalIterator {
        private:
            std::stack<std::shared_ptr<Node>> forwardStack;
            std::stack<std::shared_ptr<Node>> backupStack;

        public:
            using value_type = std::shared_ptr<Node>;
            using pointer = value_type*;
            using reference = value_type&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;
        /**
         * @brief Constructor to initialize the iterator with the root node.
         * @param root Pointer to the root node of the octree.
         */
            explicit BidirectionalIterator(std::shared_ptr<Node> root) {
                if (root != nullptr) {
                    forwardStack.push(root);
                }
            }

        /**
         * @brief Dereference operator to get the current node.
         * @return Reference to the current node.
         */    
            reference operator*() {
                if (forwardStack.empty()) {
                    throw std::out_of_range("Stack of iterator's is empty");
                }
                return forwardStack.top();
            }

        /**
         * @brief Prefix increment operator to move to the next node.
         * @return Reference to the current iterator.
         */    
            BidirectionalIterator& operator++() {
                if (forwardStack.empty()){ 
                    return *this;
                }
                auto currentNode = forwardStack.top();
                forwardStack.pop();
                backupStack.push(currentNode);
                for (int i = 7; i >= 0; --i) {
                    if (currentNode->children[i]) {
                        forwardStack.push(currentNode->children[i]);
                    }
                }
                return *this; 
            }

        /**
         * @brief Prefix decrement operator to move back to the previous node.
         * @return Reference to the current iterator.
         */    
            BidirectionalIterator& operator--() {
                if (backupStack.empty()) return *this;
                auto prevNode = backupStack.top();
                backupStack.pop();
                forwardStack.push(prevNode);
                return *this;
            }
        /**
         * @brief Not equal operator for comparison with another iterator.
         * @param other The other iterator to compare.
         * @return True if the iterators are not equal, otherwise false.
         */
            bool operator!=(const BidirectionalIterator& other) const {
                return forwardStack != other.forwardStack || backupStack != other.backupStack;
            }
        /**
         * @brief Check if there is a next node in the iteration.
         * @return True if there is a next node, otherwise false.
         */
            bool hasNext() const {
                return !forwardStack.empty();
            }
         /**
         * @brief Check if there is a previous node in the iteration.
         * @return True if there is a previous node, otherwise false.
         */
            bool hasPrev() const {
                return !backupStack.empty();
            }
    };
    private:
        std::shared_ptr<Node> root;
        decltype(T::x) MIN_SIZE = 1;
    public:


        using value_type = N;
        using size_type = std::size_t;
        using reference = N&;
        using const_reference = const N&;
        using iterator = BidirectionalIterator;
        using const_iterator = BidirectionalIterator;
        using difference_type = std::ptrdiff_t;


        Octree(){}
        Octree(BoundingBox<T> bbox) {
            root = std::make_shared<Node>(bbox);
        }


        BidirectionalIterator begin() {
            return BidirectionalIterator(root);
        }

        BidirectionalIterator end() {
            return BidirectionalIterator(nullptr);
        }

        BidirectionalIterator cbegin() const {
            return BidirectionalIterator(root);
        }

        BidirectionalIterator cend() const {
            return BidirectionalIterator(nullptr);
        }

    /**
     * @brief Get the root node of the octree.
     * @return A shared pointer to the root node.
     */
        std::shared_ptr<Node>  getRoot(){
            return root;
        }

    /**
     * @brief Create a bidirectional iterator for the octree.
     * @return A BidirectionalIterator for traversing the octree nodes.
     */

    /**
     * @brief Check for collisions with a container at a specific point.
     * @param container The container to check for collisions against.
     * @param p The point where the collision is checked.
     * @return True if a collision is detected, otherwise false.
     */
        bool checkCollisions(N container, const T& p) const {
        ContainerPosition<T> pos = calculateContainerPosition(p.x, p.y, p.z, container); 
        BidirectionalIterator it = cbegin();
        if(!root->box.contains(pos.LLDown) || !root->box.contains(pos.LLUp) ||
        !root->box.contains(pos.LRUp) ||  !root->box.contains(pos.LRDown) ||
        !root->box.contains(pos.RLDown) || !root->box.contains(pos.RLUp) ||
        !root->box.contains(pos.RRUp) || !root->box.contains(pos.RRDown)){
            return true;
        }
        while (it.hasNext()) {
            auto currentNode = *it;
            if (checkCollision(container, pos, currentNode->con)) {
                return true;
            }
            ++it;
        }
        return false;
    }

    /**
     * @brief Clone the octree.
     * @return A new cloned octree.
     */
        Octree Clone() const{
            auto clone = Octree(this->root->box);
            return clone;
        }

    /**
     * @brief Remove a container from the octree.
     * @param p Position of the point to be removed.
     * @return True if the removal was successful, otherwise false.
     */
        bool remove(const T& p){
            bool collision = false;
            std::shared_ptr<Node> copy = nullptr;
            removeR(p, root, collision, copy);
            if(collision == false){
                return false;
            }
            collision = false;
            Update(copy);
            return true;
        }

    /**
     * @brief Search for a specific container based on its position.
     * @param p Position of the container to search for.
     * @return A pair of ContainerPosition and associated data.
     * @throws std::invalid_argument if the item is not found.
     */
        std::pair<ContainerPosition<T>, N> search(const T& p) const{
            std::pair<ContainerPosition<T>, N> copyCache;
            bool found = false;
            searchR(p, root, copyCache, found);
            if(found == false){
                throw std::invalid_argument("Item not found");
            }
            return copyCache;
        }

    /**
     * @brief Perform a depth search through the octree.
     * @return Vector of pairs of ContainerPosition and associated data.
     */
        std::vector<std::pair<ContainerPosition<T>, N>> searchDepth() const{
            std::vector<std::pair<ContainerPosition<T>, N>> copyCache(0);
            searchDepth(root, copyCache);
            return copyCache;
        }

    /**
     * @brief Search and insert a container at a specified point.
     * @param container The container to be inserted.
     * @param p The position of the container.
     * @return True if the insertion was successful, otherwise false.
     */
        bool SearchInsert(N container, const T& p) const{
            ContainerPosition<T> pos = calculateContainerPosition(p.x, p.y, p.z, container);
            bool collision = false;
            std::shared_ptr<Node> copyCache = nullptr;
            std::vector<std::pair<ContainerPosition<T>, N>> copy(0);
            SearchInsert(container, pos, root, copyCache, copy, collision);
            if(copyCache == nullptr){
                return false;
            }
            return true;
        }

    /**
     * @brief Get the minimum x-coordinate from the container position (const version).
     * 
     * This function computes the minimum x-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The minimum x-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */
        static decltype(auto) getMinX(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::min({position.LLDown.x, position.LLUp.x, position.LRDown.x, position.LRUp.x, position.RRDown.x, position.RRUp.x, position.RLDown.x, position.RLUp.x});
        }
    /**
     * @brief Get the maximum x-coordinate from the container position (const version).
     * 
     * This function computes the maximum x-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The maximum x-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */
        static decltype(auto) getMaxX(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::max({position.LLDown.x, position.LLUp.x, position.LRDown.x, position.LRUp.x, position.RRDown.x, position.RRUp.x, position.RLDown.x, position.RLUp.x});
        }
    /**
     * @brief Get the minimum y-coordinate from the container position (const version).
     * 
     * This function computes the minimum y-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The minimum y-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */

        static decltype(auto) getMinY(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::min({position.LLDown.y, position.LLUp.y, position.LRDown.y, position.LRUp.y, position.RRDown.y, position.RRUp.y, position.RLDown.y, position.RLUp.y});
        }

    /**
     * @brief Get the maximum y-coordinate from the container position (const version).
     * 
     * This function computes the maximum y-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The maximum y-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */
        static decltype(auto) getMaxY(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::max({position.LLDown.y, position.LLUp.y, position.LRDown.y, position.LRUp.y, position.RRDown.y, position.RRUp.y, position.RLDown.y, position.RLUp.y});
        }


    /**
     * @brief Get the minimum z-coordinate from the container position (const version).
     * 
     * This function computes the minimum z-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The minimum z-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */
        static decltype(auto) getMinZ(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::min({position.LLDown.z, position.LLUp.z, position.LRDown.z, position.LRUp.z, position.RRDown.z, position.RRUp.z, position.RLDown.z, position.RLUp.z});
        }

    /**
     * @brief Get the maximum z-coordinate from the container position (const version).
     * 
     * This function computes the maximum z-coordinate among all corners 
     * of the given `ContainerPosition<T>` instance. It asserts that 
     * the type T fulfills the `PointConcept`.
     * 
     * @param position A constant reference to a `ContainerPosition<T>` object.
     * @return The maximum z-coordinate as `decltype(auto)`.
     * @throws static_assert If T does not satisfy the `PointConcept`.
     */
        static decltype(auto) getMaxZ(const ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "ContainerPosition<T> должен удовлетворять ContainerPositionConcept");
            return std::max({position.LLDown.z, position.LLUp.z, position.LRDown.z, position.LRUp.z, position.RRDown.z, position.RRUp.z, position.RLDown.z, position.RLUp.z});
        }

    /**
     * @brief Push a container into the octree at a specified point.
     * 
     * This function calculates the container's position using its dimensions 
     * and checks for the appropriate insertion point in the octree.
     * 
     * @param container The container to be pushed into the octree.
     * @param p The point (coordinates) where the container should be inserted.
     * @return True if the push operation is successful, otherwise false.
     */
        bool push(N container, T p){
            ContainerPosition<T> position = calculateContainerPosition(p.x, p.y, p.z, container);
            std::shared_ptr<Node> target = SearchPush(container, position);
            return insert(container, position, target);
        }
    /**
     * @brief Check if a point is within a specified container position.
     * 
     * This function checks if the provided point falls within the bounds defined by 
     * the corners of the `ContainerPosition<T>`.
     * 
     * @param p The point to be checked.
     * @param position A reference to a `ContainerPosition<T>` object.
     * @return True if the point is inside the container; otherwise, false.
     */
        static bool pointincontainer(T& p, ContainerPosition<T>& position){
            static_assert(PointConcept<T>, "T должен удовлетворять PointConcept");
            decltype(auto) minX = getMinX(position);
            decltype(auto) maxX = getMaxX(position);
            decltype(auto) minY = getMinY(position);
            decltype(auto) maxY = getMaxY(position);
            decltype(auto) minZ = getMinZ(position);
            decltype(auto) maxZ = getMaxZ(position);
            return (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY && p.z >= minZ && p.z <= maxZ);
        }

        /**
         * @brief Calculate the container positions based on its dimensions and coordinates.
         * 
         * This method computes the corners of the container position based on its size
         * and translations in 3D space.
         * 
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param z Z coordinate.
         * @param container The container for which the position is calculated.
         * @return A `ContainerPosition<T>` object that represents the positions of the container.
         * 
         * @throws static_assert If the coordinates or container cannot be combined.
         */

       static ContainerPosition<T> calculateContainerPosition(decltype(T::x) x, decltype(T::x) y, decltype(T::x) z, N container) {
            
            static_assert(CanAdd<T, N>, "Концепции неудовлетворены");

            ContainerPosition<T> pos;

            
            using Handler = ContainerHandler<std::decay_t<N>>;
            auto l = Handler::getLength(container);
            auto w = Handler::getWidth(container);
            auto h = Handler::getHeight(container);

        
            pos.LLDown.x = x;
            pos.LLDown.y = y;
            pos.LLDown.z = z;

            pos.LLUp.x = x;
            pos.LLUp.y = y;
            pos.LLUp.z = z + h;

            pos.LRDown.x = x + l;
            pos.LRDown.y = y;
            pos.LRDown.z = z;

            pos.LRUp.x = x + l;
            pos.LRUp.y = y;
            pos.LRUp.z = z + h;

            pos.RRDown.x = x + l;
            pos.RRDown.y = y + w;
            pos.RRDown.z = z;

            pos.RRUp.x = x + l;
            pos.RRUp.y = y + w;
            pos.RRUp.z = z + h;

            pos.RLDown.x = x;
            pos.RLDown.y = y + w;
            pos.RLDown.z = z;

            pos.RLUp.x = x;
            pos.RLUp.y = y + w;
            pos.RLUp.z = z + h;

            return pos;
        }


        private:

        bool insert(N container, ContainerPosition<T>& position, std::shared_ptr<Node> target){
            if(target == nullptr){
                return false;
            }
            target->con.push_back(std::make_pair(position, container));
            if (target->con.empty() == false && target->con.size() > MAX_ITEMS && target->isLeaf()){
                std::cout << "Split\n";
                split(target);
            }
            return true;
        }

        void split(std::shared_ptr<Node> node) {
            if (!node){
                return;
            }
            if (node->children[0] != nullptr){
                return;
            }

            decltype(auto) min = node->box.min;
            decltype(auto) max = node->box.max;

            decltype(auto) midX = (min.x + max.x) / 2;
            decltype(auto) midY = (min.y + max.y) / 2;
            decltype(auto) midZ = (min.z + max.z) / 2;

            BoundingBox<T> box0 = BoundingBox<T>(min, T(midX, midY, midZ));
            BoundingBox<T> box1 = BoundingBox<T>(T(midX, min.y, min.z), T(max.x, midY, midZ));
            BoundingBox<T> box2 = BoundingBox<T>(T(min.x, midY, min.z), T(midX, max.y, midZ));
            BoundingBox<T> box3 = BoundingBox<T>(T(midX, midY, min.z), T(max.x, max.y, midZ));
            BoundingBox<T> box4 = BoundingBox<T>(T(min.x, min.y, midZ), T(midX, midY, max.z));
            BoundingBox<T> box5 = BoundingBox<T>(T(midX, min.y, midZ), T(max.x, midY, max.z));
            BoundingBox<T> box6 = BoundingBox<T>(T(min.x, midY, midZ), T(midX, max.y, max.z));
            BoundingBox<T> box7 = BoundingBox<T>(T(midX, midY, midZ), max);

            if(!box0.isValid(MIN_SIZE) || !box1.isValid(MIN_SIZE)
            || !box2.isValid(MIN_SIZE) || !box3.isValid(MIN_SIZE)
            ||!box4.isValid(MIN_SIZE) || !box5.isValid(MIN_SIZE)
            ||!box6.isValid(MIN_SIZE) || !box7.isValid(MIN_SIZE)){
                return;
            }

            node->children[0] = std::make_shared<Node>(box0); // 0: мин
            node->children[1] = std::make_shared<Node>(box1); // 1: x+
            node->children[2] = std::make_shared<Node>(box2); // 2: y+
            node->children[3] = std::make_shared<Node>(box3); // 3: xy+
            node->children[4] = std::make_shared<Node>(box4); // 4: z+
            node->children[5] = std::make_shared<Node>(box5); // 5: x+z+
            node->children[6] = std::make_shared<Node>(box6); // 6: y+z+
            node->children[7] = std::make_shared<Node>(box7); // 7: xyz+
            node->children[0]->parent = node;
            node->children[1]->parent = node;
            node->children[2]->parent = node;
            node->children[3]->parent = node;
            node->children[4]->parent = node;
            node->children[5]->parent = node;
            node->children[6]->parent = node;
            node->children[7]->parent = node;
            
            for (auto it = node->con.begin(); it != node->con.end(); ) {
                bool moved = false;

                for (int i = 0; i < 8; ++i) {
                    if (node->children[i]->box.contains(it->first.LLDown) && 
                        node->children[i]->box.contains(it->first.LLUp) &&
                        node->children[i]->box.contains(it->first.LRDown) &&
                        node->children[i]->box.contains(it->first.LRUp) &&
                        node->children[i]->box.contains(it->first.RLDown) &&
                        node->children[i]->box.contains(it->first.RLUp) &&
                        node->children[i]->box.contains(it->first.RRDown) &&
                        node->children[i]->box.contains(it->first.RRUp)) {
                        node->children[i]->con.push_back(*it);
                        moved = true;
                        break;
                    }
                }

                if (moved) {
                    it = node->con.erase(it);
                } else {
                    ++it;
                }
            }
        }



        void  searchUnderOct(std::shared_ptr<Node> node, std::vector<std::pair<ContainerPosition<T>, N>>& vec) const{
            if(node == nullptr){
                return;
            }
            if(!node->con.empty()){
                vec.insert(vec.end(), node->con.begin(), node->con.end());
            }
            for(int i = 0; i < 8; ++i){
                searchUnderOct(node->children[i], vec);
            }
        }


        void searchDepth(std::shared_ptr<Node> node, std::vector<std::pair<ContainerPosition<T>, N>>& copyCache) const{
            if(node == nullptr){
                return;
            }
            if(!node->con.empty()){
                (copyCache).insert((copyCache).end(), node->con.begin(), node->con.end());
            }
            for(int i = 0; i < 8; ++i){
                searchDepth(node->children[i], copyCache);
            }
        }


        bool SearchInsert(N container, ContainerPosition<T> pos, std::shared_ptr<Node> node, std::shared_ptr<Node>& copyCache, std::vector<std::pair<ContainerPosition<T>, N>>& copy, bool& collision) const{
            if(node == nullptr){
                return false;
            }
             if (!node->box.contains(pos.LLDown) || !node->box.contains(pos.LLUp) ||
                !node->box.contains(pos.LRDown) || !node->box.contains(pos.LRUp) ||
                !node->box.contains(pos.RLDown) || !node->box.contains(pos.RLUp) ||
                !node->box.contains(pos.RRDown) || !node->box.contains(pos.RRUp)) {
                return false;
            }
            if(!node->con.empty()){
                (copy).insert((copy).end(), node->con.begin(), node->con.end());
            }
            if (node->isLeaf() == false && collision == false && copyCache == nullptr) {
                for (size_t i = 0; i < 8; ++i) {
                     SearchInsert(container, pos, node->children[i], copyCache, copy, collision);
                }
            }
            if(collision == false && copyCache == nullptr){
                
                searchUnderOct(node, copy);
                
                if(!checkCollision(container, pos, copy)){
                    copyCache = node;
                    return true;
                }else{
                    collision = true;
                    return false;
                }
            }else if(collision == false && copyCache != nullptr){
                return true;
            }
            return false;
        }



        std::shared_ptr<Node> SearchPush(N container, ContainerPosition<T> pos) const{
            bool collision = false;
            std::shared_ptr<Node> copyCache = nullptr;
            std::vector<std::pair<ContainerPosition<T>, N>> copy(0);
            SearchInsert(container, pos, root, copyCache, copy, collision);
            return copyCache;
        }


            void searchR(T id, std::shared_ptr<Node> node, std::pair<ContainerPosition<T>, N>& copyCache, bool& flag)const{
                if(node == nullptr){
                    return;
                }
                if(!node->box.contains(id)){
                    return;
                }
                if(node->con.empty() == false){
                    for(auto& i : node->con){
                        if(i.first.LLDown.x != -1  && (i.first.LLDown) == id){
                            flag = true;
                            copyCache = std::make_pair(i.first, i.second);
                            return;
                        }
                    }
                }
                if(node->isLeaf() == false){
                    for(int i = 0; i < 8; ++i){
                        searchR(id, node->children[i], copyCache, flag);
                    }
                }
            }


            void removeR(T id, std::shared_ptr<Node> node, bool& collision, std::shared_ptr<Node>& copyCache){
                if(node == nullptr){
                    return;
                }
                if(collision == true || node == nullptr){
                    return;
                }
                if(!node->box.contains(id)){
                    return;
                }
                if(node->con.empty() == false){
                    for(auto& i : node->con){
                        if(i.first.LLDown.x != -1  && i.first.LLDown == id){
                            /*if(i.second != nullptr)*/{
                                node->con.erase(std::remove(node->con.begin(), node->con.end(), i), node->con.end());
                            }
                            collision = true;
                            copyCache = node;
                            return;
                        }
                    }
                }
                if(node->isLeaf() == false){
                    for(int i = 0; i < 8; ++i){
                        removeR(id, node->children[i], collision, copyCache);
                    }
                }

            }


            bool checkEmptyNode(std::shared_ptr<Node> node) const{
            if (node == nullptr) return true;
            for (int i = 0; i < 8; ++i) {
                if (node->children[i] != nullptr && !node->children[i]->con.empty()) {
                    return false;
                }
            }
            return true;
        }

           void mearge(std::shared_ptr<Node> node) {
                if (node == nullptr || node->isLeaf()) return;
                for (int i = 0; i < 8; ++i) {
                    if (node->children[i] != nullptr && !node->children[i]->con.empty()) {
                        node->con.insert(node->con.end(), node->children[i]->con.begin(), node->children[i]->con.end());
                        node->children[i]->con.clear();
                    }
                }
                for (int i = 0; i < 8; ++i) {
                    mearge(node->children[i]);
                }
            }

            void decreaseHightTree(std::shared_ptr<Node> node) {
                if (node == nullptr || node->isLeaf()) {
                    return;
                }
                for (int i = 0; i < 8; ++i) {
                    decreaseHightTree(node->children[i]);
                }
                if (checkEmptyNode(node)) {
                    for (int i = 0; i < 8; ++i) {
                        if (node->children[i] != nullptr && node->children[i]->isLeaf()) { 
                            node->children[i].reset();
                            node->children[i] = nullptr;
                        }
                    }
                }
            }


            void Update(std::shared_ptr<Node> node) {
                 auto parentNode = node->parent.lock(); 
                if(node == root && node->isLeaf() == false && node->con.empty()){
                    mearge(node);
                    decreaseHightTree(node);
                    return;
                }
                if(checkEmptyNode(parentNode)){
                    mearge(parentNode);
                    decreaseHightTree(parentNode);
                }
            }


            bool ContainEntity(ContainerPosition<T> pos1, ContainerPosition<T> pos2) const {
                
                int pos1MinX = getMinX(pos1);
                int pos1MaxX = getMaxX(pos1);
                int pos1MinY = getMinY(pos1);
                int pos1MaxY = getMaxY(pos1);
                int pos1MinZ = getMinZ(pos1);
                int pos1MaxZ = getMaxZ(pos1);
                

                int pos2MinX = getMinX(pos2);
                int pos2MaxX = getMaxX(pos2);
                int pos2MinY = getMinY(pos2);
                int pos2MaxY = getMaxY(pos2);
                int pos2MinZ = getMinZ(pos2);
                int pos2MaxZ = getMaxZ(pos2);


                return (pos1MinX <= pos2MaxX && pos1MaxX >= pos2MinX) &&
                    (pos1MinY <= pos2MaxY && pos1MaxY >= pos2MinY) &&
                    (pos1MinZ <= pos2MaxZ && pos1MaxZ >= pos2MinZ);
            }


            bool checkCollision(N container, ContainerPosition<T> pos, std::vector<std::pair<ContainerPosition<T>, N>> copy) const {
                for(auto it : copy){
                    if(ContainEntity(it.first, pos)){
                        return true;
                    }
                }
                return false; 
            }

                
};


#endif