// Zachary Motassim
// simplified dynamic array implementation
#include<iostream>
#include<algorithm> // sort
template<typename Dynamic>
class DynamicArray{

  // data members
  private:
    size_t size_       ;   // actual size
    Dynamic *array_    ;  //        array
    size_t end_pointer ; //  logical size

    // private helpers
    // set size of array
    void SetSize(size_t size_){
    this->size_=size_;
    array_=new Dynamic[size_] ;
    }

    // takes old smaller array and larger new array and copys over all contents
      void CopyOver(size_t old_size,size_t new_size){
        Dynamic* temp = new Dynamic[ old_size ] ; // hold old arrays so things to be copied over
        temp = array_ ;
        SetSize(new_size);
        for(size_t i = 0 ; i < end_pointer ; ++i ) {
          array_[i] = temp[i] ;
        }
        delete[] temp; temp = nullptr ;
      }

      // will be called when either completely empty or full
        void resize(){ //  zero param resize
          if(size_==0) {
            SetSize(100);
            return;
          }// if array is full elements are copied over and new size is set
          CopyOver(size_,size_*2) ;
        }

  public:

  // default constructor. giving members default values
    DynamicArray(){size_=0; end_pointer=0; array_=nullptr;}

    // one param to set size
    DynamicArray(size_t size_){SetSize(size_);end_pointer=0;}
  // big 5
  // copy constructor. copying values from one class instance form another
    DynamicArray(const DynamicArray& rhs) {
			size_ = rhs.size_;
      end_pointer = rhs.end_pointer ;
			array_ = new Dynamic[size_];
			for (size_t i = 0 ; i < end_pointer ; i++) {
				array_[ i ] = rhs.array_[ i ] ;
			   }
	   }

  // copy assignment, overloading = to copy elements from one class instance to another
    DynamicArray& operator=( const DynamicArray& rhs ) {
			DynamicArray copy = rhs;
			std::swap( *this , copy ) ;
			return *this ;
		  }

    // move constructor, taking everyhting from one class instance, putting it into another and clearing the prev one
    DynamicArray(DynamicArray&& rhs) {
      size_ = rhs.size_;
      end_pointer = rhs.end_pointer;
      array_ = rhs.array_;
      rhs.size_ = 0;
      rhs.end_pointer = 0 ;
      rhs.array_ = nullptr;
      }

    // move assignment
    DynamicArray& operator=( DynamicArray&& rhs ) {
        std::swap( size_ , rhs.size_ ) ;
        std::swap( array_ , rhs.array_ ) ;
        std::swap( end_pointer , rhs.end_pointer ) ;
        return *this;
      }

    // deconstructor, delete allocated memory on heap
    ~DynamicArray( ) {delete[] array_  ; array_ = nullptr ; }
  // end of big 5

  // returns logical size of array
    size_t size()const{return end_pointer;}

    void clear(){
      SetSize(0);
      end_pointer=0;
    }

    void resize( size_t new_size ) { // one param resize for user
      if( end_pointer != 0 ) { // array has elems and should be copied over into diff size array
        CopyOver(size_,new_size) ;
        return ;
      }
      // case where array is inizialized, has size 0
      end_pointer = new_size ;
      SetSize(new_size) ;
    }

// insert at end
  void pushback( Dynamic x ) {
    if(end_pointer==size_){resize();} // condition will be fulfilled weather empty or full
    array_[end_pointer]=x;
    end_pointer++ ;
  }

// inserts at given position i
  void insert( Dynamic x , size_t i ) {
    if(end_pointer+1==size_) { resize( ) ;}
    if( i==end_pointer ) { pushback( x ) ; return ; } // insert is called at end, just call pushback
    bool pos_found = false;
    size_t pos = end_pointer  ;
    end_pointer++;
    while(!pos_found){
      array_[pos]=array_[pos-1] ;
      pos-- ;
      if(pos==i){pos_found=true;}
      }
    array_[pos] = x ;
  }

// erase last element
  void pop_back(){end_pointer--;}

// erases at position
  void erase( size_t i ) {
    bool pos_found = false;
    if(i==end_pointer-1){pop_back();return;}
    int pos = i ;
    while(!pos_found) {
      array_[pos]=array_[pos+1] ;
      pos++ ;
      if( pos==end_pointer-1 ){pos_found=true;}
    }
    end_pointer--;
}

  // two param will erase start-end elements
  void erase( size_t start , size_t end ){
    while(start!=end){
      erase(start);
      end--;
    }
  }

  // checks if logically empty
  bool empty(){return end_pointer==0;}

  void sort(){std::sort(array_,array_+end_pointer);}

// accessing elements

Dynamic at( size_t i ) const {
  if( i >= end_pointer){ std::abort( ) ; }
  return array_[ i ] ;
}

// get first element
  Dynamic front() const {return at(0);}

// get last element
  Dynamic back() const {  return at(end_pointer-1);}

  Dynamic & operator []( size_t i ) { // non const allows editin
    if( i >= end_pointer){ std::abort( ) ; }
    return array_[ i ] ;
  }

  // overloaded [] to allow for direct access to array data member
  Dynamic operator []( size_t i ) const { // direct access but cannot edit
    if( i >= end_pointer){ std::abort( ) ; }
    return array_[ i ] ;
  }

// overloaded cout<<
  friend std::ostream &operator<<( std::ostream &out , const DynamicArray &arr ) {
    for ( size_t i = 0 ; i < arr.size( ) ; ++i ) {
      out << arr.array_[ i ] << " " ;
    }
    return out << std::endl ;
  }
};
