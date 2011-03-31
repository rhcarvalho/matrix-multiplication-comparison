      program matrix
      integer, dimension(:,:), allocatable :: v, A, x

c     variables to measure time
      real t1, t2
      
      integer n, n_min, n_max, count, step
      integer i, j
      
c     read parameters from standard input
      character(len=10) :: arg
      if (iargc() .ne. 3) then
         write(*,*) "Required arguments: MIN MAX COUNT"
         call exit(1)
      end if

      call getarg(1, arg)
      read (arg,*) n_min
      call getarg(2, arg)
      read (arg,*) n_max
      call getarg(3, arg)
      read (arg,*) count
      step = (n_max - n_min) / (count - 1)

      write(*,*)"[1] Compute v = Ax looping through rows then columns
     &(i, j)"
      write(*,*)"[2] Compute v = Ax looping through columns then rows
     &(j, i)"
      write(*,'(A6,A10,A10)') "N	","[1]	","[2]"

c     main iteration
      do n = n_min, n_max, step
      
c     allocate memory for arrays
      allocate(v(n,1))
      allocate(A(n,n))
      allocate(x(n,1))
      
c     initialize arrays
      do i = 1, n
         v(i,1) = 0
         do j = 1, n
            A(i,j) = int(rand()*1000)-500
         end do
         x(i,1) = int(rand()*1000)-500
      end do
      
c     compute elapsed time
      t1 = compute_ij(n, v, A, x)
      t2 = compute_ji(n, v, A, x)
      write(*,'(I6,A1,F9.6,A1,F9.6)') n,'	',t1,'	',t2
      
c     deallocate memory
      deallocate(v)
      deallocate(A)
      deallocate(x)
      end do
      end

      real function compute_ij(n, v, A, x)
      integer, dimension(n,n) :: A
      integer, dimension(n,1) :: v, x
      real start_time, stop_time

      call cpu_time(start_time)
      
      do i = 1, n
        do j = 1, n
          v(i,1) = v(i,1) + A(i,j) * x(j,1)
        end do
      end do
      
      call cpu_time(stop_time)
      compute_ij = stop_time-start_time
      end
      
      real function compute_ji(n, v, A, x)
      integer, dimension(n,n) :: A
      integer, dimension(n,1) :: v, x
      real start_time, stop_time

      call cpu_time(start_time)
      
      do j = 1, n
        do i = 1, n
          v(i,1) = v(i,1) + A(i,j) * x(j,1)
        end do
      end do
      
      call cpu_time(stop_time)
      compute_ji = stop_time-start_time
      end
      
