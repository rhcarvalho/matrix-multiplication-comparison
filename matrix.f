      program matrix
      integer, dimension(:,:), allocatable :: A, x, y

c     variables to measure time
      real t1, t2
      
      integer n, n_min, n_max, step
      integer i, j
      
c     read parameters from standard input
      write(*,*) "Write: min max count"
      read (*,*) n_min, n_max, step

      write(*,*) "compute_ij","compute_ji"

c     main iteration
      do n = n_min, n_max, step
      
c     allocate memory for arrays
      allocate( A(n,n) )
      allocate( x(n,1) )
      allocate( y(n,1) )
      
c     generate values for arrays A and x
      do i = 1, n
        do j = 1, n
          A(i,j) = int(rand()*1000)-500
        end do
        x(i,1) = int(rand()*1000)-500
      end do
      
c     print matrix A and vector x
c      write(*,*) "A:"
c      do i = 1, n
c        do j = 1, n
c          write(*,*) A(i,j)
c        end do
c        write(*,*) ''
c      end do

c      write(*,*) "x:"
c      do i = 1, n
c        write(*,*) x(i,1)
c      end do
      
c     compute elapsed time
      t1 = compute_ij(n, A, x, y)

      t2 = compute_ji(n, A, x, y)
      write(*,*) t1, t2
      
c     deallocate memory
      deallocate(A)
      deallocate(x)
      deallocate(y)
      
      end do
      end

      real function compute_ij(n, A, x, y)
      integer, dimension(n,n) :: A
      integer, dimension(n,1) :: x, y
      real start_time, stop_time
      
      do i = 1, n
        y(i,1) = 0
      end do

      call cpu_time( start_time )
      
      do i = 1, n
        do j = 1, n
          y(i,1) = y(i,1) + A(i,j) * x(j,1)
        end do
      end do
      
      call cpu_time( stop_time )
      compute_ij = stop_time-start_time
      
c      write(*,*) 'y:'
c      do i = 1, n
c        write(*,*) y(i,1)
c      end do
      end
      
      real function compute_ji(n, A, x, y)
      integer, dimension(n,n) :: A
      integer, dimension(n,1) :: x, y
      real start_time, stop_time
      
      do i = 1, n
        y(i,1) = 0
      end do

      call cpu_time( start_time )
      
      do j = 1, n
        do i = 1, n
          y(i,1) = y(i,1) + A(i,j) * x(j,1)
        end do
      end do
      
      call cpu_time( stop_time )
      compute_ji = stop_time-start_time
      
c      write(*,*) 'y:'
c      do i = 1, n
c        write(*,*) y(i,1)
c      end do
      end
      
