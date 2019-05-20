.. include:: ../../global.txt

.. _sec-saving-diagnostics:

Saving time series of spatially-varying diagnostic quantities
-------------------------------------------------------------

Sometimes it is useful to have PISM save a handful of diagnostic *maps* at some interval
like every 10 years or even every month. One can use snapshots (section
:ref:`sec-snapshots`), but doing so can easily fill your hard-drive because snapshots are
complete (i.e. re-startable) model states. Sometimes you want a *subset* of model
variables saved frequently in an output file.

Use options ``-extra_file``, ``-extra_times``, and ``-extra_vars`` for this. For example,

.. code-block:: none

   pismr -i foo.nc -y 10000 -o output.nc -extra_file extras.nc \
         -extra_times 0:10:1e4 -extra_vars velsurf_mag,velbase_mag


will run for 10000 years, saving the magnitude of horizontal velocities at the ice surface
and at the base of ice every 10 years. Times are specified using a comma-separated list or
a MATLAB-style range. See :numref:`tab-extras` for all the options controlling this
feature. The section :ref:`sec-extra_vars` list all the variable choices.

Note that options :opt:`-extra_times`, :opt:`-save_times`, :opt:`-ts_times` take *dates*
if a non-trivial calendar is selected. For example,

.. code-block:: bash

   pismr ... -extra_times 10       # every 10 years
   pismr ... -extra_times 2days    # every 2 days
   pismr ... -calendar gregorian -extra_times 1-1-1:daily:11-1-1 # daily for 10 years
   pismr ... -calendar gregorian -extra_times daily -ys 1-1-1 -ye 11-1-1
   pismr ... -calendar gregorian -extra_times 2hours -ys 1-1-1 -ye 1-2-1


The step in the range specification can have the form ``Nunit``, for example ``5days``.
Units based on "months" and "years" are not supported if a non-trivial calendar is
selected.

In addition to specifying a constant step in ``-extra_times a:step:b`` one can save every
hour, day, month, or every year by using ``hourly``, ``daily``, ``monthly`` or ``yearly``
instead of a number; for example

.. code-block:: none

   pismr -i foo.nc -y 100 -o output.nc -extra_file extras.nc \
         -extra_times 0:monthly:100 -extra_vars dHdt

will save the rate of change of the ice thickness every month for 100 years. With
``-calendar none`` (the default), "monthly" means "every :math:`\frac 1 {12}` of the
year", and "yearly" is "every :math:`3.14\ldots\times10^7`" seconds, otherwise PISM uses
month lengths computed using the selected calendar.

It is frequently desirable to save diagnostic quantities at regular intervals for the
whole duration of the run; options :opt:`-extra_times`, :opt:`-ts_times`, and
:opt:`-save_times` provide a shortcut. For example, use ``-extra_times yearly`` to save at
the end of every year.

This is especially useful when using a climate forcing file to set run duration:

.. code-block:: none

   pismr -i foo.nc -surface given -surface_given_file climate.nc \
         -calendar gregorian -time_file climate.nc \
         -extra_times monthly -extra_file ex.nc -extra_vars thk


will save ice thickness at the end of every month while running PISM for the duration of
climate forcing data in ``climate.nc``.

Times given using ``-extra_times`` describe the reporting intervals by giving the
endpoints of these reporting intervals. The save itself occurs at the end of each
interval. This implies, for example, that ``0:1:10`` will produce 10 records at times
1,...,10 and *not* 11 records.

If the file ``foo.nc``, specified by ``-extra_file foo.nc``, already exists then by
default the existing file will be moved to ``foo.nc~`` and the new time series will go
into ``foo.nc``. To append the time series onto the end of the existing file, use option
``-extra_append``.

The list of available diagnostic quantities depends on the model setup. For example, a run
with only one vertical grid level in the bedrock thermal layer will not be able to save
``litho_temp``, an SIA-only run does not use a basal yield stress model and so will not
provide ``tauc``, etc. To see which quantities are available in a particular setup, use
the :opt:`-list_diagnostics` option, which prints the list of diagnostics and stops.

The ``-extra_file`` mechanism modifies PISM's adaptive time-stepping scheme so as to step
to, and save at, *exactly* the times requested. By contrast, as noted in subsection
:ref:`sec-saving-time-series`, the ``-ts_file`` mechanism does not alter PISM's time-steps
and instead uses linear interpolation to save at the requested times in between PISM's
actual time-steps.

.. list-table:: Command-line options controlling extra diagnostic output
   :name: tab-extras
   :header-rows: 1
   :widths: 1,3

   * - Option
     - Description

   * - :opt:`-extra_file`
     - Specifies the file to save to; should be different from the output (:opt:`-o`)
       file.

   * - :opt:`-extra_times`
     - Specifies times to save at either as a MATLAB-style range :math:`a:\Delta t:b` or a
       comma-separated list.

   * - :opt:`-extra_vars`
     - Comma-separated list of variables

   * - :opt:`-extra_split`
     - Save to separate files, similar to :opt:`-save_split`.

   * - :opt:`-extra_append`
     - Append variables to file if it already exists. No effect if file does not yet
       exist, and no effect if :opt:`-extra_split` is set.
